// Copyright (C) 2019 ExtraHash
//
// Please see the included LICENSE file for more information.
import React, { Component } from 'react';
import ReactLoading from 'react-loading';
import ReactTooltip from 'react-tooltip';
import { session } from '../index';

type Props = {
  size: string,
  darkMode: boolean
};

type State = {
  syncStatus: number,
  daemonSyncStatus: number,
  walletHeight: number,
  daemonHeight: number,
  networkHeight: number
};

export default class SyncStatus extends Component<Props, State> {
  props: Props;

  state: State;

  syncInterval: IntervalID;

  constructor(props?: Props) {
    super(props);
    const [walletHeight, daemonHeight, networkHeight] = this.getSyncHeights();
    this.state = {
      syncStatus: session.getSyncStatus(),
      daemonSyncStatus: session.getDaemonSyncStatus(),
      walletHeight,
      daemonHeight,
      networkHeight
    };
    this.syncInterval = setInterval(() => this.refresh(), 1000);
  }

  componentDidMount() {}

  componentWillUnmount() {
    clearInterval(this.syncInterval);
  }

  getSyncHeights() {
    if (!session.wallet) {
      return [0, 0, 0];
    }
    return session.wallet.getSyncStatus();
  }

  refresh() {
    const [walletHeight, daemonHeight, networkHeight] = this.getSyncHeights();
    this.setState(() => ({
      syncStatus: session.getSyncStatus(),
      daemonSyncStatus: session.getDaemonSyncStatus(),
      walletHeight,
      daemonHeight,
      networkHeight
    }));
    ReactTooltip.rebuild();
  }

  renderStatusTag(
    status: number,
    isConnected: boolean,
    tooltip: string,
    size: string
  ) {
    if (!isConnected) {
      return (
        <span
          className={`tag is-danger ${size} sync-status`}
          data-tip={tooltip}
        >
          <ReactLoading
            type="spinningBubbles"
            color="#F5F5F5"
            height={25}
            width={25}
          />
        </span>
      );
    }

    if (status >= 100) {
      return (
        <span
          className={`tag is-success ${size} sync-status`}
          data-tip={tooltip}
        >
          {status}%
        </span>
      );
    }

    return (
      <span
        className={`tag is-warning ${size} sync-status`}
        data-tip={tooltip}
      >
        {status}%
        <ReactLoading type="bubbles" color="#fff0f5" height={30} width={30} />
      </span>
    );
  }

  render() {
    const {
      syncStatus,
      daemonSyncStatus,
      walletHeight,
      daemonHeight,
      networkHeight
    } = this.state;
    const { darkMode, size } = this.props;
    const color = darkMode ? 'is-dark' : 'is-white';

    let syncTooltip;
    let daemonTooltip;

    if (session.wallet) {
      syncTooltip =
        networkHeight === 0
          ? 'Connecting, please wait...'
          : `${walletHeight}/${networkHeight}`;
      daemonTooltip =
        networkHeight === 0
          ? 'Connecting, please wait...'
          : `${daemonHeight}/${networkHeight}`;
    } else {
      syncTooltip = 'No wallet open!';
      daemonTooltip = 'No wallet open!';
    }
    return (
      <React.Fragment>
        <div className="control statusicons">
          <div className="tags has-addons">
            <span
              className={
                darkMode ? `tag ${color} ${size}` : `tag ${color} ${size}`
              }
            >
              Node:
            </span>
            {this.renderStatusTag(
              daemonSyncStatus,
              networkHeight !== 0,
              daemonTooltip,
              size
            )}
          </div>
        </div>
        <div className="control statusicons">
          <div className="tags has-addons">
            <span
              className={
                darkMode ? `tag ${color} ${size}` : `tag ${color} ${size}`
              }
            >
              Sync:
            </span>
            {this.renderStatusTag(
              syncStatus,
              networkHeight !== 0,
              syncTooltip,
              size
            )}
          </div>
        </div>
      </React.Fragment>
    );
  }
}
