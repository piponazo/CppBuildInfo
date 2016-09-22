ExternalProject_Add(gtest
    PREFIX "${PROJECT_BINARY_DIR}/gtest"
    INSTALL_DIR "${PROJECT_BINARY_DIR}/install"

    GIT_REPOSITORY https://github.com/google/googletest.git

    CMAKE_ARGS -Dgtest_force_shared_crt=ON
               -DBUILD_SHARED_LIBS=ON
               -Dgtest_disable_pthreads=ON
               -Dgtest_build_tests=OFF
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/install
               -DBUILD_GTEST=ON
               -DBUILD_GMOCK=OFF

    UPDATE_DISCONNECTED 1
)
