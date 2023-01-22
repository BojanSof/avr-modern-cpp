include(CPM)

CPMAddPackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG main
    EXCLUDE_FROM_ALL true
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt"
)