# Build up test image here
IMAGE_INSTALL += "\
        liboqs \
"

DEFAULT_TEST_SUITES:pn-${PN} = "ssh ping ptest"

