#!/bin/bash
set -e # Enables cheking of return values from each command
set -x # Prints every command

if [[ "$(uname -s)" == 'Linux' ]]; then
    sudo apt-get install cmake python-pip
    sudo apt-get install --allow-unauthenticated -qq g++-5 gcc-5
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 80 --slave /usr/bin/g++ g++ /usr/bin/g++-5 --slave /usr/bin/gcov gcov /usr/bin/gcov-5
    sudo apt-get install qtbase5-dev qt5-default qttools5-dev-tools
    sudo pip install virtualenv
    virtualenv conan
    source conan/bin/activate
fi

python --version
pip install urllib3[secure] -U #Should solve SSL issues
pip install conan==1.8.3
#pip install codecov
conan --version
conan config set storage.path=~/conanData
mkdir -p ~/.conan/profiles
