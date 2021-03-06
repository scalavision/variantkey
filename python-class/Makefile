# MAKEFILE
#
# @author      Nicola Asuni <nicola.asuni@genomicsplc.com>
# @link        https://github.com/genomicsplc/variantkey
# ------------------------------------------------------------------------------

# List special make targets that are not associated with files
.PHONY: help version build wheel format clean

# Project name
PROJECT=variantkey

# Project version
VERSION=$(shell cat ../VERSION)

# Project release number (packaging build number)
RELEASE=$(shell cat ../RELEASE)

# Include conda channels
include ../conda/channels.mk

# Conda environment
CONDA_ENV=../../env-${PROJECT}

# Current directory
CURRENTDIR=$(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# --- MAKE TARGETS ---

# Display general help about this command
help:
	@echo ""
	@echo "${PROJECT} Python Makefile."
	@echo "The following commands are available:"
	@echo ""
	@echo "    make test    : Run the unit tests against source code"
	@echo "    make build   : Build and test a minified version of the library"
	@echo "    make wheel   : Build a Wheel package"
	@echo "    make format  : Format the source code"
	@echo "    make clean   : Remove any build artifact"
	@echo ""

all: clean format build

# Set the version from VERSION file
version:
	sed -i "s/variantkey >=.*$$/variantkey >=$(VERSION)/" ../conda/python-class/meta.yaml
	sed -i "s/version:.*$$/version: $(VERSION)/" ../conda/python-class/meta.yaml
	sed -i "s/number:.*$$/number: $(RELEASE)/" ../conda/python-class/meta.yaml
	sed -i "s/version=.*,$$/version='$(VERSION).$(RELEASE)',/" setup.py
	sed -i "s/'variantkey>=.*',$$/'variantkey>=$(VERSION).$(RELEASE)',/" setup.py

# Build a minified version of the library
build: version
	../conda/setup-conda.sh
	PROJECT_ROOT=${CURRENTDIR} ${CONDA_ENV}/bin/conda build --prefix-length 128 --no-anaconda-upload --override-channels $(ARTIFACTORY_CONDA_CHANNELS) -c ${CONDA_ENV}/conda-bld/linux-64 ../conda/python-class

# Build a Wheel package
wheel: clean version
	python3 setup.py sdist bdist_wheel

# Format the source code
format:
	autopep8 --in-place --max-line-length=255 pyvariantkey/*.py
	autopep8 --in-place --max-line-length=255 test/*.py

# Remove any build artifact
clean:
	rm -rf htmlcov build dist .cache .benchmarks tests/*.so tests/__pycache__ pyvariantkey/__pycache__ pyvariantkey.egg-info
	find . -type f -name '*.pyc' -exec rm -f {} \;
