#! /bin/bash

set -e

cleanup() {
  echo "\n### Cleanup test files ###\n"

  if [ -d ${CWD}/install ]; then
    rm -Rf ${CWD}/install
  fi
  if [ -d ./test/build ]; then
    rm -Rf ./test/build
  fi
  if [ -d ./test2/build ]; then
    rm -Rf ./test2/build
  fi
}

trap "cleanup; echo '!!ERROR: Test FAILED'; exit 1" ERR SIGHUP SIGINT SIGTERM

CWD=`pwd`

echo "\n### Configure test ###\n"

if [ -d ${CWD}/test/build ]; then
  rm -Rf ${CWD}/test/build/*
else
  mkdir -p ${CWD}/test/build
fi
cd ${CWD}/test/build
cmake -DCMAKE_INSTALL_PREFIX=${CWD}/install/test ..

echo "\n### Build and install test ###\n"

make -j install
cd ${CWD}

echo "\n### Configure test ###\n"

if [ -d ${CWD}/test2/build ]; then
  rm -Rf ${CWD}/test2/build/*
else
  mkdir -p ${CWD}/test2/build
fi
cd ${CWD}/test2/build
cmake -DCMAKE_INSTALL_PREFIX=${CWD}/install/test2 -DTESTFINDTBB_ROOT_DIR=${CWD}/install/test ..

echo "\n### Build and install test2 ###\n"

make -j install
cd ${CWD}

echo "\n### Test running the applications ###\n"

cd ${CWD}
${CWD}/test/build/test_tbb_a
${CWD}/test/build/test_tbb_b
${CWD}/test2/build/test_tbb
${CWD}/install/test/bin/test_tbb_a
${CWD}/install/test/bin/test_tbb_b
${CWD}/install/test2/bin/test_tbb

cleanup

echo "Tests completed successfully"
