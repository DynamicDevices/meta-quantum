# Build up test image here
IMAGE_INSTALL += "\
        ptest-runner \
        liboqs \
"

DEFAULT_TEST_SUITES:pn-${PN} = "ssh ping ptest"

