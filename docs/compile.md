# traaittEnterpriseXTE wallet

![image](https://github.com/TRRXITTE/traaitt/blob/master/docs/XTE.png)

![Download Count](https://img.shields.io/github/downloads/trrxitte/traaittenterprisexte/total.svg)
![Version](https://img.shields.io/github/v/release/trrxitte/traaittenterprisexte)
![GitHub stars](https://img.shields.io/github/stars/TRRXITTE/traaittenterprisexte?label=Github%20Stars)


#### traaittEnterpriseXTE: [official GitHub Download](https://GitHub.com/trrxitte/traaittEnterpriseXTE/releases)
<img src="https://raw.githubusercontent.com/trrxitte/traaittenterprisexte/master/screenshots/xte.png">

## Development Setup (All Platforms)

### Dependencies

#### You will need the following dependencies installed before you can proceed to the "Setup" step:

- Node.JS (Latest LTS version - 10.x) https://nodejs.org/

- Yarn https://yarnpkg.com/en/

- Git https://git-scm.com/downloads

Tip: If you already have a different version of node.js installed besides 10.x, try using [Node Version Manager](https://github.com/nvm-sh/nvm#install--update-script).

#### Setup

First, clone the repo via git:

```bash
git clone https://github.com/TRRXITTE/traaittEnterpriseXTE.git
```

And then install the dependencies with yarn.

```bash
$ cd traaittEnterpriseXTE
$ yarn
```

Run the wallet.

```bash
$ yarn start
```

### Starting Development

Start the app in the `dev` environment. This starts the renderer process in [**hot-module-replacement**](https://webpack.js.org/guides/hmr-react/) mode and starts a webpack dev server that sends hot updates to the renderer process:

```bash
$ yarn dev
```

### Packaging

To package apps for the local platform:

```bash
$ yarn package
```

## License

© [TRRXITTE Int., incorporate](https://github.com/TRRXITTE)
See included License file for more details.