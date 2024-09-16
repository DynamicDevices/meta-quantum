# Build up test image here
IMAGE_INSTALL += "\
        ptest-runner \
        liboqs \
        liboqs-ptest \
"

DEFAULT_TEST_SUITES:pn-${PN} = "ssh ping ptest"

