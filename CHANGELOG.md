# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [0.9.0](https://github.com/airbus-cyber/aum/releases/tag/0.9.0)

### Added
- macro AUM_MAIN_RUN to replace the hand-written main function
- README.md
- flag -Wmissing-declarations when compiling source
- target install to Makefile
- aum.pc into the RPM package

### Deprecated
- all functions in aum/runner.h in favor of macro AUM_MAIN_RUN

### Changed
- Simplified console output


## [0.8.1](https://github.com/airbus-cyber/aum/releases/tag/0.8.1)

### Fixed
- the .so was not included in the generated RPM package


## [0.8.0](https://github.com/airbus-cyber/aum/releases/tag/0.8.0)

### Added
- RPM packaging


## [0.7.0](https://github.com/airbus-cyber/aum/releases/tag/0.7.0)

### Added
- Debian packaging


## [0.6.1](https://github.com/airbus-cyber/aum/releases/tag/0.6.1)

### Fixed
- default target in Makefile was failing in the absence of the .git directory
- target `debian` was incorrectly documented in Makefile


## [0.6.0](https://github.com/airbus-cyber/aum/releases/tag/0.6.0)

### Added
- First open source release

