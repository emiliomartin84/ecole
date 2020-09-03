# Matrix built with different compilers (e.g. gcc9, clang10).
ARG compiler=clang10

# --------------------

# Build and runtime dependencies in a image with different compiler and different python version
FROM conanio/${compiler} AS builder
USER root
ARG python_version=3.6

# Install minimal dependencies for a CircleCI image, install miniconda, and install Ecole
# dependencies.
RUN apt-get update && \
    apt-get install -y --no-install-recommends wget git openssh-client tar gzip ca-certificates && \
    apt-get clean && \
    pyenv install miniconda3-latest && \
    pyenv global miniconda3-latest
# We could get compilers from conda, but we want to avoid having compile flags set by conda as it
# can interfer with coverage and sanitizers.
# Still getting cmake... to make sure it finds scip and other conda packages
RUN conda install --channel scipopt --channel conda-forge \
        cmake make conan \
        scip pyscipopt python="${python_version}" pybind11 numpy xtensor-python \
        pytest pytest-cov && \
    conda clean --all --yes && \
    `# Temporary override pybind11 version to 2.5 otherwise pinned by xtensor-python` \
    `# Until https://github.com/conda-forge/xtensor-python-feedstock/pull/65 is merged ` \
    wget https://github.com/pybind/pybind11/archive/v2.5.0.tar.gz -O pybind11-2.5.0.tgz && \
    tar -xzf pybind11-2.5.0.tgz && \
    cmake -B build -S pybind11-2.5.0 -D PYBIND11_TEST=OFF -D PYTHON_EXECUTABLE="$(pyenv which python)" && \
    cmake --build build && \
    cmake --install build --prefix "/opt/pyenv/versions/miniconda3-latest/" && \
    rm -rf pybind11-2.5.0.tgz pybind11-2.5.0 build

WORKDIR /app

# --------------------

# Code analysis dependencies
FROM builder AS checker
RUN apt-get update && \
    apt-get install --yes --no-install-recommends \
        clang-format-${LLVM_VERSION} clang-tidy-${LLVM_VERSION} && \
    update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-${LLVM_VERSION} 100 && \
    update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-${LLVM_VERSION} 100 && \
    apt-get clean && \
    pip install --no-cache-dir pre-commit

# --------------------

# Documentation generator dependencies
FROM builder AS documenter
RUN conda install -c conda-forge doxygen sphinx'>=3.0' breathe'>=4.15' sphinx_rtd_theme && \
    conda clean --all --yes
