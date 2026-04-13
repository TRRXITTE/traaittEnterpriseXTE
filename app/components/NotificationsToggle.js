// Copyright (C) 2019 ExtraHash
//
// Please see the included LICENSE file for more information.
import React, { Component } from 'react';
import {
  session,
  config,
  requestNotificationPermission,
  supportsOsNotifications
} from '../index';
import uiType from '../utils/uitype';

type State = {
  notifications: boolean,
  permissionBlocked: boolean
};

type Props = {
  darkMode: boolean
};

export default class NotificationsToggle extends Component<Props, State> {
  constructor(props: Props) {
    super(props);
    this.state = {
      // Read live from config so it reflects current persisted value
      notifications: config.notifications !== undefined ? config.notifications : true,
      permissionBlocked:
        !supportsOsNotifications() &&
        'Notification' in window &&
        window.Notification.permission === 'denied'
    };
    this.toggle = this.toggle.bind(this);
  }

  componentWillMount() {}

  componentWillUnmount() {}

  toggle = () => {
    const { notifications } = this.state;
    const enabling = !notifications;

    if (enabling && supportsOsNotifications()) {
      session.modifyConfig('notifications', true);
      this.setState({
        notifications: true,
        permissionBlocked: false
      });
      return;
    }

    if (enabling && 'Notification' in window) {
      if (window.Notification.permission === 'denied') {
        this.setState({ permissionBlocked: true });
        return;
      }
      if (window.Notification.permission === 'default') {
        requestNotificationPermission().then(permission => {
          if (permission === 'granted') {
            session.modifyConfig('notifications', true);
            // Reflect the live persisted value
            this.setState({
              notifications: true,
              permissionBlocked: false
            });
          } else {
            this.setState({ permissionBlocked: permission === 'denied' });
          }
        });
        return;
      }
    }

    session.modifyConfig('notifications', enabling);
    // Sync state from config so the toggle always reflects persisted value
    this.setState({
      notifications: enabling,
      permissionBlocked: false
    });
  };

  render() {
    const { darkMode } = this.props;
    const { textColor } = uiType(darkMode);
    const { notifications, permissionBlocked } = this.state;
    return (
      <div>
        {permissionBlocked && (
          <p className="has-text-danger" style={{ marginBottom: '0.5rem' }}>
            Notifications are blocked by the OS. Enable them in System Settings.
          </p>
        )}
        {notifications === false && (
          <span className={textColor}>
            <a
              className="button is-danger"
              onClick={this.toggle}
              onKeyPress={this.toggle}
              role="button"
              tabIndex={0}
            >
              <span className="icon is-large">
                <i className="fas fa-times" />
              </span>
            </a>
            &nbsp;&nbsp; Notifications: <b>Off</b>
          </span>
        )}
        {notifications === true && (
          <span className={textColor}>
            <a
              className="button is-success"
              onClick={this.toggle}
              onKeyPress={this.toggle}
              role="button"
              tabIndex={0}
            >
              <span className="icon is-large">
                <i className="fa fa-check" />
              </span>
            </a>
            &nbsp;&nbsp; Notifications: <b>On</b> &nbsp;&nbsp;
          </span>
        )}
      </div>
    );
  }
}
