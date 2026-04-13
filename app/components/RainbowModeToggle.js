// Copyright (C) 2019 ExtraHash
//
// Please see the included LICENSE file for more information.
import React, { Component } from 'react';
import uiType from '../utils/uitype';
import { session, eventEmitter } from '../index';

type State = {
  rainbowMode: boolean
};

type Props = {
  darkMode: boolean
};

export default class RainbowModeToggle extends Component<Props, State> {
  constructor(props: Props) {
    super(props);
    this.state = {
      rainbowMode: session.rainbowMode === true
    };
    this.rainbowModeOn = this.rainbowModeOn.bind(this);
    this.rainbowModeOff = this.rainbowModeOff.bind(this);
  }

  componentDidMount() {
    eventEmitter.on('rainbowmodeon', this.syncRainbowModeOn);
    eventEmitter.on('rainbowmodeoff', this.syncRainbowModeOff);
    eventEmitter.on('darkmodeoff', this.syncRainbowModeOff);
  }

  componentWillUnmount() {
    eventEmitter.off('rainbowmodeon', this.syncRainbowModeOn);
    eventEmitter.off('rainbowmodeoff', this.syncRainbowModeOff);
    eventEmitter.off('darkmodeoff', this.syncRainbowModeOff);
  }

  syncRainbowModeOn = () => {
    this.setState({
      rainbowMode: session.rainbowMode === true && session.darkMode === true
    });
  };

  syncRainbowModeOff = () => {
    this.setState({
      rainbowMode: false
    });
  };

  rainbowModeOn = () => {
    const shouldEnableDarkMode = session.darkMode !== true;
    this.setState({
      rainbowMode: true
    });
    session.toggleRainbowMode(true);
    if (shouldEnableDarkMode) {
      eventEmitter.emit('darkmodeon');
    }
    eventEmitter.emit('rainbowmodeon');
  };

  rainbowModeOff = () => {
    this.setState({
      rainbowMode: false
    });
    session.toggleRainbowMode(false);
    eventEmitter.emit('rainbowmodeoff');
  };

  render() {
    const { darkMode } = this.props;
    const { rainbowMode } = this.state;
    const { textColor } = uiType(darkMode);
    return (
      <div>
        {rainbowMode === true && (
          <span className={textColor}>
            <a
              className="button rainbow-mode-button"
              onClick={this.rainbowModeOff}
              onKeyPress={this.rainbowModeOff}
              role="button"
              tabIndex={0}
            >
              <span className="icon is-large has-text-white">
                <i className="fas fa-palette" />
              </span>
            </a>
            &nbsp;&nbsp; Rainbow Legacy: <b>On</b>
          </span>
        )}
        {rainbowMode === false && (
          <span className={textColor}>
            <a
              className="button rainbow-mode-button rainbow-mode-button-off"
              onClick={this.rainbowModeOn}
              onKeyPress={this.rainbowModeOn}
              role="button"
              tabIndex={0}
            >
              <span className="icon is-large has-text-warning">
                <i className="fas fa-palette" />
              </span>
            </a>
            &nbsp;&nbsp; Rainbow Legacy: <b>Off</b>
          </span>
        )}
      </div>
    );
  }
}
