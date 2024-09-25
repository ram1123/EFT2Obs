#!/usr/bin/env bash
export LHAPDF_CONFIG_PATH="${PWD}/lhapdf/bin/lhapdf-config"
export PYTHONPATH="${PWD}/lhapdf/lib64/python2.7/site-packages:${PYTHONPATH}"
export LD_LIBRARY_PATH="${PWD}/lhapdf/lib:${LD_LIBRARY_PATH}"
export RIVET_ANALYSIS_PATH=${PWD}/RivetPlugins
# export MG_DIR="MG5_aMC_v3_5_4"
# export MG_TARBALL="MG5_aMC_v3.5.4.tar.gz"
# https://launchpad.net/mg5amcnlo/3.0/3.5.x/+download/MG5_aMC_v2.9.19.tar.gz
export MG_DIR="MG5_aMC_v2_9_19"
export MG_TARBALL="MG5_aMC_v2.9.19.tar.gz"
export RIVET_VERSION="4.0.0"
export DEBUG_SCRIPTS=0

if [ -f "local/rivetenv.sh" ]; then
	source local/rivetenv.sh
fi

if [ "$DEBUG_SCRIPTS" -eq "1" ]; then
	set -x
fi

if [[ ! -z "$PYTHIA8DATA" ]]; then
        export PYTHIA8DATA=""
fi

#[[ ":$PYTHONPATH:" != *":$PWD/${MG_DIR}:"* ]] && PYTHONPATH="$PWD/${MG_DIR}:${PYTHONPATH}"
