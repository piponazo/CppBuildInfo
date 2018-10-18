#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    brew update || brew update
    brew outdated pyenv || brew upgrade pyenv
    brew install pyenv-virtualenv
    brew install cmake || true

    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi

    pyenv install 2.7.10
    pyenv virtualenv 2.7.10 conan
    pyenv rehash
    pyenv activate conan
else
    sudo apt-get update
    sudo apt-get install cmake
    sudo apt-get install python-pip
    sudo pip install virtualenv
    virtualenv conan
    source conan/bin/activate
fi

pip install conan_package_tools # It install conan too
conan user
