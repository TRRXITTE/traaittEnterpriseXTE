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
    const [walletHeight, , networkHeight] = session.wallet.getSyncStatus();
    const syncStatus = session.getSyncStatus();
    this.setState({ syncStatus, walletHeight, networkHeight });
  }

  render() {
    const { syncStatus, walletHeight, networkHeight } = this.state;
    const { darkMode } = this.props;

    if (syncStatus >= 100 || networkHeight === 0) {
      return null;
    }

    const textColor = darkMode ? 'has-text-white' : 'has-text-grey-dark';

    return (
      <div className="sync-progress-bar-wrap">
        <p className={`is-size-7 ${textColor} sync-progress-label`}>
          Syncing blocks:&nbsp;
          <strong className={textColor}>
            {walletHeight.toLocaleString()}
          </strong>
          &nbsp;/&nbsp;
          <strong className={textColor}>
            {networkHeight.toLocaleString()}
          </strong>
          &nbsp;&nbsp;({syncStatus}%)
        </p>
        <progress
          className="progress is-warning is-small sync-progress-bar"
          value={syncStatus}
          max="100"
        >
          {syncStatus}%
        </progress>
      </div>
    );
  }
}
