<h1 align="center">Bloqcoin [BLOQ, ฿]</h1>

Bloqcoin is a new kind of storage, incentivized by cryptoeconomics. The Bloqcoin software allows anyone to operate a node in the Bloqcoin blockchain networks. It is adapted from Bloqcoin and other cryptocurrencies.

**Website:** [bloqcoin.org](https://www.bloqcoin.org/)

## Usage

To start your journey with Bloqcoin, see the [installation guide](doc/README.md).

The JSON-RPC API provided by Bloqcoin is self-documenting and can be browsed with `bloqcoin-cli help`, while detailed information for each command can be viewed with `bloqcoin-cli help <command>`.

### Ports

Bloqcoin by default uses port `28333` for peer-to-peer communication that
is needed to synchronize the "mainnet" blockchain and stay informed of new
transactions and blocks. Additionally, a JSONRPC port can be opened, which
defaults to port `28332` for mainnet nodes. It is strongly recommended to not
expose RPC ports to the public internet.

| Function | mainnet | testnet | signet  | regtest |
| :------- | ------: | ------: | ------: | ------: |
| P2P      |   28333 |   38333 |   48333 |   18444 |
| RPC      |   28332 |   38332 |   48332 |   18332 |

## Ongoing development

Bloqcoin is an open source and community driven software. The development
process is open and publicly visible; anyone can see, discuss and work on the
software.

Main development resources:

* [GitHub Projects](https://github.com/bloqcoin/bloqcoin/projects) is used to
  follow planned and in-progress work for upcoming releases.
* [GitHub Discussion](https://github.com/bloqcoin/bloqcoin/discussions) is used
  to discuss features, planned and unplanned, related to both the development of
  the Bloqcoin software, the underlying protocols and the BLOQ asset.

## Contributing

If you find a bug or experience issues with this software, please report it
using the [issue system](https://github.com/bloqcoin/bloqcoin/issues/new?assignees=&labels=bug&template=bug_report.md&title=%5Bbug%5D+).

Please see [the contribution guide](CONTRIBUTING.md) to see how you can
participate in the development of Bloqcoin. There are often
[topics seeking help](https://github.com/bloqcoin/bloqcoin/labels/help%20wanted)
where your contributions will have high impact and get very appreciation. wow.

## Frequently Asked Questions

Do you have a question regarding Bloqcoin? An answer is perhaps already in the
[FAQ](doc/FAQ.md) or the
[Q&A section](https://github.com/bloqcoin/bloqcoin/discussions/categories/q-a)
of the discussion board!

## License

Bloqcoin is released under the terms of the MIT license. See
[COPYING](COPYING) for more information or see
[opensource.org](https://opensource.org/licenses/MIT)
