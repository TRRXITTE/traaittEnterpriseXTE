// Copyright (C) 2019 ExtraHash
//
// Please see the included LICENSE file for more information.
import React, { Component } from 'react';
import log from 'electron-log';
import { Daemon } from '@trrxitte/xte-wallet-backend';
import { il8n, session, eventEmitter, config } from '../index';
import uiType from '../utils/uitype';

const DEFAULT_NODE_PORT = '14485';

const REMOTE_NODES = [
  'main.trrxitte.com:14485',
  'eu-west.trrxitte.com:14485',
  'eu-west-2.trrxitte.com:14485',
  'us-east.trrxitte.com:14485',
  'us-west.trrxitte.com:14485',
  'sa-east.trrxitte.com:14485',
  'asia-sea.trrxitte.com:14485',
  'asia-east.trrxitte.com:14485',
  'asie-nea.trrxitte.com:14485'
];

type Props = {
  darkMode: boolean
};

type State = {
  connectednode: string,
  nodeChangeInProgress: boolean,
  ssl: boolean | void
};

export default class NodeChanger extends Component<Props, State> {
  props: Props;

  state: State;

  constructor(props: Props) {
    super(props);
    this.daemonInfo =
      session && session.wallet
        ? session.wallet.getDaemonConnectionInfo()
        : {
            host: config.daemonHost,
            port: config.daemonPort,
            ssl: config.daemonSSL
          };

    this.state = {
      connectednode: `${this.daemonInfo.host}:${this.daemonInfo.port}`,
      nodeChangeInProgress: false,
      ssl:
        this.daemonInfo.sslDetermined === false
          ? undefined
          : this.daemonInfo.ssl
    };
    this.changeNode = this.changeNode.bind(this);
    this.handleNodeInputChange = this.handleNodeInputChange.bind(this);
    this.handleNodeSelectChange = this.handleNodeSelectChange.bind(this);
    this.handleNewNode = this.handleNewNode.bind(this);
    this.handleNodeChangeInProgress = this.handleNodeChangeInProgress.bind(
      this
    );
    this.handleNodeChangeComplete = this.handleNodeChangeComplete.bind(this);
  }

  componentWillMount() {
    eventEmitter.on('newNodeConnected', this.handleNewNode);
    eventEmitter.on('nodeChangeInProgress', this.handleNodeChangeInProgress);
    eventEmitter.on('nodeChangeComplete', this.handleNodeChangeComplete);
  }

  componentWillUnmount() {
    eventEmitter.off('newNodeConnected', this.handleNewNode);
    eventEmitter.off('nodeChangeInProgress', this.handleNodeChangeInProgress);
    eventEmitter.off('nodeChangeComplete', this.handleNodeChangeComplete);
  }

  changeNode = async (event: any) => {
    event.preventDefault();
    const { connectednode } = this.state;
    const connectionString = connectednode.trim();
    // eslint-disable-next-line prefer-const
    let [host, port] = connectionString.split(':', 2);
    if (!host) {
      return;
    }
    host = host.trim();
    if (port === undefined) {
      port = DEFAULT_NODE_PORT;
    }
    port = port.trim() || DEFAULT_NODE_PORT;
    const normalizedNode = `${host}:${port}`;
    this.setState({
      connectednode: normalizedNode
    });
    if (
      // eslint-disable-next-line eqeqeq
      host == session.daemonHost &&
      // eslint-disable-next-line eqeqeq
      port == session.daemonPort.toString()
    ) {
      return;
    }
    eventEmitter.emit('nodeChangeInProgress');
    try {
      const daemon = new Daemon(host, Number(port));
      await session.wallet.swapNode(daemon);
      session.daemon = daemon;
      const daemonInfo = session.wallet.getDaemonConnectionInfo();
      session.daemonHost = daemonInfo.host;
      session.daemonPort = daemonInfo.port;
      log.info(`Connected to ${daemonInfo.host}:${daemonInfo.port}`);
      session.modifyConfig('daemonHost', daemonInfo.host);
      session.modifyConfig('daemonPort', daemonInfo.port);
      if (daemonInfo.sslDetermined) {
        session.modifyConfig('daemonSSL', daemonInfo.ssl);
      }
      eventEmitter.emit('newNodeConnected');
    } catch (error) {
      log.error(`Failed to connect to ${normalizedNode}`);
      log.error(error);
      const daemonInfo = session.daemon.getConnectionInfo();
      this.setState({
        nodeChangeInProgress: false,
        connectednode: `${session.daemonHost}:${session.daemonPort}`,
        ssl: daemonInfo.sslDetermined === false ? undefined : daemonInfo.ssl
      });
    }
  };

  handleNodeInputChange = (event: any) => {
    this.setState({ connectednode: event.target.value.trim() });
  };

  handleNodeSelectChange = (event: any) => {
    if (!event.target.value) {
      return;
    }
    this.setState({ connectednode: event.target.value });
  };

  getSelectedNodeValue(connectednode: string) {
    return REMOTE_NODES.includes(connectednode) ? connectednode : '';
  }

  handleNewNode = () => {
    const daemonInfo = session.wallet.getDaemonConnectionInfo();

    this.setState({
      nodeChangeInProgress: false,
      connectednode: `${daemonInfo.host}:${daemonInfo.port}`,
      ssl: daemonInfo.sslDetermined === false ? undefined : daemonInfo.ssl
    });
  };

  handleNodeChangeInProgress = () => {
    this.setState({
      nodeChangeInProgress: true,
      ssl: undefined
    });
  };

  handleNodeChangeComplete = () => {
    const daemonInfo = session.daemon.getConnectionInfo();
    this.setState({
      nodeChangeInProgress: false,
      connectednode: `${session.daemonHost}:${session.daemonPort}`,
      ssl: daemonInfo.sslDetermined === false ? undefined : daemonInfo.ssl
    });
  };

  render() {
    const { darkMode } = this.props;
    const { textColor } = uiType(darkMode);
    const { nodeChangeInProgress, connectednode, ssl } = this.state;
    return (
      <form onSubmit={this.changeNode}>
        <p className={`has-text-weight-bold ${textColor}`}>
          Remote network (ip:port)
        </p>
        <div className="field node-select-field">
          <div className="control is-expanded">
            <div className="select is-fullwidth">
              <select
                value={this.getSelectedNodeValue(connectednode)}
                onChange={this.handleNodeSelectChange}
                disabled={nodeChangeInProgress}
              >
                <option value="">Select a remote node...</option>
                {REMOTE_NODES.map(node => (
                  <option value={node} key={node}>
                    {node}
                  </option>
                ))}
              </select>
            </div>
          </div>
        </div>
        <div className="field has-addons is-expanded">
          <div className="control is-expanded has-icons-left">
            {nodeChangeInProgress === false && (
              <input
                className="input has-icons-left"
                type="text"
                value={connectednode}
                onChange={this.handleNodeInputChange}
              />
            )}
            {ssl === true && (
              <span className="icon is-small is-left">
                <i className="fas fa-lock" />
              </span>
            )}
            {ssl === false && (
              <span className="icon is-small is-left">
                <i className="fas fa-unlock" />
              </span>
            )}
            {nodeChangeInProgress === true && (
              <input
                className="input"
                type="text"
                placeholder="connecting..."
                onChange={this.handleNodeInputChange}
              />
            )}
            {nodeChangeInProgress === true && (
              <span className="icon is-small is-left">
                <i className="fas fa-sync fa-spin" />
              </span>
            )}
          </div>
          {nodeChangeInProgress === true && (
            <div className="control">
              <button type="submit" className="button is-success is-loading">
                <span className="icon is-small">
                  <i className="fa fa-network-wired" />
                </span>
                &nbsp;&nbsp;{il8n.connect}
              </button>
            </div>
          )}
          {nodeChangeInProgress === false && (
            <div className="control">
              <button type="submit" className="button is-success">
                <span className="icon is-small">
                  <i className="fa fa-network-wired" />
                </span>
                &nbsp;&nbsp;{il8n.connect}
              </button>
            </div>
          )}
        </div>
      </form>
    );
  }
}
