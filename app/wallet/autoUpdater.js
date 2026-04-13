// Copyright (C) 2019 ExtraHash
//
// Please see the included LICENSE file for more information.
import request from 'request-promise';
import log from 'electron-log';
import semver from 'semver';
import os from 'os';
import { eventEmitter } from '../index';
import npmPackage from '../../package.json';

const currentVersion = npmPackage.version;
const operatingSystem = os.platform();
const arch = os.arch();
const releasesURL =
  'https://api.github.com/repos/TRRXITTE/traaittEnterpriseXTE/releases?per_page=20';
const releaseDownloadURL =
  'https://github.com/TRRXITTE/traaittEnterpriseXTE/releases/latest';

function normalizeInstalledVersion(version: string) {
  const rawVersion = String(version || '')
    .trim()
    .replace(/^v/i, '');
  const coercedVersion = semver.coerce(rawVersion);
  return semver.valid(rawVersion) || (coercedVersion && coercedVersion.version);
}

function normalizeStableReleaseVersion(version: string) {
  const rawVersion = String(version || '')
    .trim()
    .replace(/^v/i, '');

  if (/-rc/i.test(rawVersion)) {
    return null;
  }

  const exactVersion = semver.valid(rawVersion);
  if (exactVersion) {
    const parsedVersion = semver.parse(exactVersion);
    return parsedVersion && parsedVersion.prerelease.length === 0
      ? parsedVersion.version
      : null;
  }

  const stableVersion = rawVersion.match(/\b(\d+\.\d+\.\d+)\b/);
  return stableVersion ? stableVersion[1] : null;
}

function findAssetDownloadURL(release: any) {
  const assets = Array.isArray(release.assets) ? release.assets : [];
  const platformMatchers = {
    darwin: [/\.dmg$/i],
    win32: [/setup.*\.exe$/i, /\.exe$/i],
    linux:
      arch === 'arm64'
        ? [/arm64.*\.AppImage$/i, /\.AppImage$/i]
        : [/(x86_64|amd64).*\.AppImage$/i, /\.AppImage$/i]
  };

  const matchers = platformMatchers[operatingSystem] || [];
  for (let i = 0; i < matchers.length; i++) {
    const matcher = matchers[i];
    const asset = assets.find(item => matcher.test(item.name));
    if (asset && asset.browser_download_url) {
      return asset.browser_download_url;
    }
  }

  return release.html_url || releaseDownloadURL;
}

function getLatestStableRelease(releases: any[]) {
  return releases
    .map(release => {
      return {
        release,
        version: normalizeStableReleaseVersion(release.tag_name || release.name)
      };
    })
    .filter(item => {
      return (
        item.version &&
        item.release &&
        item.release.draft !== true &&
        item.release.prerelease !== true
      );
    })
    .sort((a, b) => semver.rcompare(a.version, b.version))[0];
}

export default class AutoUpdater {
  async getLatestVersion() {
    if (process.env.NODE_ENV !== 'development') {
      log.debug('Checking for updates...');
      const options = {
        method: 'GET',
        url: releasesURL,
        headers: {
          Accept: 'application/vnd.github+json',
          'User-Agent': `${npmPackage.name}/${currentVersion}`
        },
        json: true,
        gzip: true,
        timeout: 1000 * 20
      };

      try {
        const releases = await request(options);
        const latestStableRelease = getLatestStableRelease(
          Array.isArray(releases) ? releases : [releases]
        );
        const installedVersion = normalizeInstalledVersion(currentVersion);

        if (!latestStableRelease) {
          log.debug('No stable GitHub release found.');
          return releases;
        }

        if (!installedVersion) {
          log.debug(`Unable to parse local version: ${currentVersion}`);
          return releases;
        }

        if (semver.gt(latestStableRelease.version, installedVersion)) {
          log.debug(
            `Update required! Local version: ${currentVersion}, latest version: ${latestStableRelease.version}`
          );
          eventEmitter.emit('updateRequired', {
            currentVersion,
            latestVersion: latestStableRelease.version,
            downloadPath: findAssetDownloadURL(latestStableRelease.release),
            releaseURL: latestStableRelease.release.html_url || releaseDownloadURL
          });
        } else {
          log.debug('No update found.');
        }
        return releases;
      } catch (error) {
        log.debug('Error when contacting GitHub release API...', error);
        return null;
      }
    } else {
      log.debug('Development environment detected.');
      return null;
    }
  }
}
