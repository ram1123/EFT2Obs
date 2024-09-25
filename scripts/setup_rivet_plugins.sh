#!/usr/bin/env bash
set -e

source env.sh

if [ -z "${RIVET_ANALYSIS_PATH}" ]; then echo "ERROR: environment variable RIVET_ANALYSIS_PATH is not set"; exit 1; fi

pushd RivetPlugins
	rivet-build RivetPlugins.so ./*.cc
popd
