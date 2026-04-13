// Copyright (C) 2019 ExtraHash
//
// Please see the included LICENSE file for more information.
import React, { Component } from 'react';
import { session } from '../index';

type Props = {
  darkMode: boolean
};

type State = {
  syncStatus: number,
  walletHeight: number,
  daemonHeight: number,
  daemonSyncStatus: number,
  networkHeight: number
};

export default class SyncProgressBar extends Component<Props, State> {
  props: Props;

  state: State;

  syncInterval: IntervalID;

  constructor(props?: Props) {
    super(props);
    this.state = {
      syncStatus: 0,
      walletHeight: 0,
      daemonHeight: 0,
      daemonSyncStatus: 0,
      networkHeight: 0
    };
    this.syncInterval = setInterval(() => this.refresh(), 1000);
  }

  componentDidMount() {
    this.refresh();
  }

  componentWillUnmount() {
    clearInterval(this.syncInterval);
  }

  refresh() {
    if (!session.wallet) return;
    const [
      walletHeight,
      daemonHeight,
      networkHeight
    ] = session.wallet.getSyncStatus();
    const syncStatus = session.getSyncStatus();
    const daemonSyncStatus = session.getDaemonSyncStatus();
    this.setState({
      syncStatus,
      walletHeight,
      daemonHeight,
      daemonSyncStatus,
      networkHeight
    });
  }

  render() {
    const {
      syncStatus,
      walletHeight,
      daemonHeight,
      daemonSyncStatus,
      networkHeight
    } = this.state;
    const { darkMode } = this.props;

    const textColor = darkMode ? 'has-text-white' : 'has-text-grey-dark';
    const isConnecting = networkHeight === 0;
    const isSynced =
      !isConnecting && syncStatus >= 100 && daemonSyncStatus >= 100;
    const progressColor = isConnecting
      ? 'is-danger'
      : isSynced
      ? 'is-success'
      : 'is-warning';
    const label = isConnecting
      ? 'Connecting to node:'
      : isSynced
      ? 'Synced blocks:'
      : 'Syncing blocks:';

    return (
      <div className="sync-progress-bar-wrap">
        <p className={`is-size-7 ${textColor} sync-progress-label`}>
          {isConnecting ? (
            <span>{label}</span>
          ) : (
            <span>
              {label}&nbsp;
              <strong className={textColor}>
                {walletHeight.toLocaleString()}
              </strong>
              &nbsp;/&nbsp;
              <strong className={textColor}>
                {networkHeight.toLocaleString()}
              </strong>
              &nbsp;({syncStatus}%)
            </span>
          )}
          {isConnecting ? (
            <span className="sync-progress-node">Node: connecting</span>
          ) : (
            <span className="sync-progress-node">
              Node:&nbsp;
              <strong className={textColor}>
                {daemonHeight.toLocaleString()}
              </strong>
              &nbsp;/&nbsp;
              <strong className={textColor}>
                {networkHeight.toLocaleString()}
              </strong>
              &nbsp;({daemonSyncStatus}%)
            </span>
          )}
        </p>
        {isConnecting ? (
          <progress
            className={`progress ${progressColor} is-small sync-progress-bar`}
            max="100"
          >
            Connecting
          </progress>
        ) : (
          <progress
            className={`progress ${progressColor} is-small sync-progress-bar`}
            value={syncStatus}
            max="100"
          >
            {syncStatus}%
          </progress>
        )}
      </div>
    );
  }
}
