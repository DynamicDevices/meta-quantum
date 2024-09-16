# Build up test image here
        ptest-runner \
        liboqs \
        liboqs-ptest \
"

DEFAULT_TEST_SUITES:pn-${PN} = "ssh ping ptest"

