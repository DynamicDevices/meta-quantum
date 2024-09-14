# meta-quantum-safe

A Yocto layer to start exploring the world of quantum safe cryptography

## Build status

| Branch | Support Status* | Status of Build & Tests |
| ------ | --------------- | ----------------------- |
| scarthgap | 	Long Term Support (until Apr. 2028) | [![scarthgap](https://img.shields.io/github/actions/workflow/status/dynamicdevices/meta-quantum-safe/CI_github.yml?branch=scarthgap&label=build%20%26%20test)](https://github.com/DynamicDevices/meta-quantum-safe/actions/workflows/CI_github.yml) |
| nanbield | 	May 2024  | [![nanbield](https://img.shields.io/github/actions/workflow/status/dynamicdevices/meta-quantum-safe/CI_github.yml?branch=nanbield&label=build%20%26%20test)](https://github.com/DynamicDevices/meta-quantum-safe/actions/workflows/CI_github.yml) |
| kirkstone | 	Long Term Support (minimum Apr. 2024)	 | [![master](https://img.shields.io/github/actions/workflow/status/dynamicdevices/meta-quantum-safe/CI_github.yml?branch=kirkstone&label=build%20%26%20test)](https://github.com/DynamicDevices/meta-quantum-safe/actions/workflows/CI_github.yml) |
| dunfell | 	Supported - Long Term Support (until Apr. 2024) | [![dunfell](https://img.shields.io/github/actions/workflow/status/dynamicdevices/meta-quantum-safe/CI_github.yml?branch=dunfell&label=build%20%26%20test)](https://github.com/DynamicDevices/meta-quantum-safe/actions/workflows/CI_github.yml) |

*support status as of 22/02/24, follows main Yocto release support schedule [here](https://wiki.yoctoproject.org/wiki/Releases)

## Open Quantum Safe Support

We currently have support for the Open Quantum Safe project library [implementation](https://openquantumsafe.org)

The intent is to next add OpenSSL and MQTT support in the near future to enable simple examples for testing quantum-safe algorithms end-to-end across the internet.

`libOQS` builds and runs on our Jaguar i.MX8M Mini based board and some performance statistics can be seen from the tool `speed_sig`.

It should also build and run on other target boards supported by Yocto. If you use this layer please do feed back your results to us in order to add supported platforms to this README and hopefully generate some comparative performance figures.

To enable the library in your build image (and optionally the tests) add this layer to your `conf/bblayers.conf`

```
BSPLAYERS += " \
  ${OEROOT}/layers/meta-quantum-safe \
"
```

Then add the `liboqj` recipe to your image

```
CORE_IMAGE_BASE_INSTALL += " \
   liboqs \
   liboqs-tests \
"
```

A quickstart on building Yocto images is [here](https://docs.yoctoproject.org/brief-yoctoprojectqs/index.html).

## TODO

### Infrastructure

- Get CI going for supported Yocto releases

### Support

- Add quantum-safe SSH daemon
- Add quanutm-safe TLS support (?)

- Make libOQJ OpenSSL support dependent on whether OpenSSL enabled in build.

### Samples

- Encrypt and decrypt a key
- Take the QS encrypted key and encrypt a message with it (symmetric key)
- Do an end to end demo over MQTT

TODO: Ask what else is needed here?

## Performance Statistics

### Jaguar i.MX8M Mini based board

```
io@imx8mm-jaguar-sentai-7130a09dab86563:/home/fio$ cat speed.log
Configuration info
==================
Target platform:  aarch64-Linux-6.8.0-40-generic
Compiler:         clang (14.0.6 (https://github.com/llvm/llvm-project f28c006a5895fc0e329fe15fead81e37457cb1d1))
Compile options:  [-march=armv8-a+crypto;-Wa,--noexecstack;-O3;-fomit-frame-pointer;-Wbad-function-cast;-Wcast-qual;-Wnarrowing;-Wconversion]
OQS version:      0.10.2-dev
Git commit:       unknown
OpenSSL enabled:  Yes (OpenSSL 3.0.14 4 Jun 2024)
AES:              OpenSSL
SHA-2:            OpenSSL
SHA-3:            C
OQS build flags:  BUILD_SHARED_LIBS OQS_LIBJADE_BUILD OQS_OPT_TARGET=generic CMAKE_BUILD_TYPE=Release
CPU exts compile-time:

Speed test
==========
Started at 2024-09-13 23:39:04
Operation                            | Iterations | Total time (s) | Time (us): mean | pop. stdev | High-prec time (ns): mean | pop. stdev
------------------------------------ | ----------:| --------------:| ---------------:| ----------:| -------------------------:| ----------:
Dilithium2                           |            |                |                 |            |                           |           
keypair                              |       4636 |          3.000 |         647.187 |     13.761 |                    646988 |      13704
sign                                 |        853 |          3.004 |        3521.379 |   2353.126 |                   3521170 |    2353136
verify                               |       4058 |          3.000 |         739.323 |      5.664 |                    739149 |       5664
Dilithium3                           |            |                |                 |            |                           |           
keypair                              |       2862 |          3.001 |        1048.447 |      8.149 |                   1048262 |       8135
sign                                 |        517 |          3.002 |        5807.215 |   4055.840 |                   5806967 |    4055827
verify                               |       2589 |          3.001 |        1159.127 |      7.355 |                   1158948 |       7344
Dilithium5                           |            |                |                 |            |                           |           
keypair                              |       1782 |          3.001 |        1684.034 |     19.457 |                   1683820 |      19451
sign                                 |        423 |          3.003 |        7098.586 |   4220.371 |                   7098344 |    4220394
verify                               |       1624 |          3.001 |        1847.775 |     25.392 |                   1847588 |      25391
ML-DSA-44-ipd                        |            |                |                 |            |                           |           
keypair                              |       4610 |          3.000 |         650.809 |     11.603 |                    650629 |      11569
sign                                 |        812 |          3.001 |        3696.126 |   2534.561 |                   3695918 |    2534589
verify                               |       4032 |          3.000 |         744.122 |      5.578 |                    743940 |       5557
ML-DSA-44                            |            |                |                 |            |                           |           
keypair                              |       4621 |          3.000 |         649.223 |      6.164 |                    649031 |       6149
sign                                 |        844 |          3.001 |        3555.642 |   2433.071 |                   3555414 |    2433039
verify                               |       4034 |          3.000 |         743.779 |      5.739 |                    743601 |       5726
ML-DSA-65-ipd                        |            |                |                 |            |                           |           
keypair                              |       2858 |          3.001 |        1050.017 |     15.211 |                   1049806 |      15180
sign                                 |        497 |          3.000 |        6036.907 |   4223.367 |                   6036691 |    4223361
verify                               |       2577 |          3.001 |        1164.536 |     19.878 |                   1164341 |      19873
ML-DSA-65                            |            |                |                 |            |                           |           
keypair                              |       2860 |          3.000 |        1049.089 |     13.140 |                   1048885 |      13131
sign                                 |        523 |          3.001 |        5737.553 |   4194.417 |                   5737335 |    4194399
verify                               |       2584 |          3.001 |        1161.245 |     12.926 |                   1161055 |      12909
ML-DSA-87-ipd                        |            |                |                 |            |                           |           
keypair                              |       1774 |          3.001 |        1691.935 |     29.670 |                   1691690 |      29643
sign                                 |        434 |          3.006 |        6925.385 |   3921.843 |                   6925169 |    3921835
verify                               |       1623 |          3.001 |        1849.010 |     23.990 |                   1848836 |      24014
ML-DSA-87                            |            |                |                 |            |                           |           
keypair                              |       1778 |          3.001 |        1687.647 |     97.322 |                   1687433 |      97328
sign                                 |        408 |          3.008 |        7373.380 |   4724.988 |                   7373090 |    4724967
verify                               |       1624 |          3.000 |        1847.526 |     22.883 |                   1847347 |      22879
Falcon-512                           |            |                |                 |            |                           |           
keypair                              |         37 |          3.029 |       81859.865 |  28251.408 |                  81859549 |   28251351
sign                                 |        168 |          3.012 |       17928.577 |     35.883 |                  17928343 |      35833
verify                               |       8624 |          3.000 |         347.891 |      4.109 |                    347714 |       4082
Falcon-1024                          |            |                |                 |            |                           |           
keypair                              |         16 |          3.316 |      207247.750 |  64415.255 |                 207247120 |   64414979
sign                                 |         77 |          3.011 |       39108.273 |     57.134 |                  39108059 |      57160
verify                               |       4378 |          3.001 |         685.384 |      6.844 |                    685212 |       6823
Falcon-padded-512                    |            |                |                 |            |                           |           
keypair                              |         39 |          3.009 |       77149.231 |  30152.085 |                  77148928 |   30152151
sign                                 |        168 |          3.013 |       17932.923 |     35.339 |                  17932760 |      35313
verify                               |       8626 |          3.000 |         347.822 |      3.445 |                    347645 |       3415
Falcon-padded-1024                   |            |                |                 |            |                           |           
keypair                              |         13 |          3.218 |      247540.692 |  81911.393 |                 247539870 |   81911305
sign                                 |         78 |          3.028 |       38821.128 |   4234.191 |                  38820802 |    4234227
verify                               |       4440 |          3.000 |         675.746 |      6.940 |                    675566 |       6928
SPHINCS+-SHA2-128f-simple            |            |                |                 |            |                           |           
keypair                              |        308 |          3.004 |        9753.942 |     66.985 |                   9753754 |      66977
sign                                 |         14 |          3.193 |      228049.714 |    579.665 |                 228049006 |     579726
verify                               |        227 |          3.013 |       13271.551 |     26.682 |                  13271370 |      26690
SPHINCS+-SHA2-128s-simple            |            |                |                 |            |                           |           
keypair                              |          5 |          3.134 |      626781.200 |    308.397 |                 626780877 |     308581
sign                                 |          1 |          4.774 |     4774235.000 |      0.000 |                4774234368 |          0
verify                               |        688 |          3.004 |        4365.706 |    150.458 |                   4365529 |     150473
SPHINCS+-SHA2-192f-simple            |            |                |                 |            |                           |           
keypair                              |        207 |          3.007 |       14524.333 |     48.847 |                  14524148 |      48820
sign                                 |          8 |          3.060 |      382526.000 |    567.443 |                 382525024 |     567187
verify                               |        148 |          3.009 |       20333.223 |     54.127 |                  20332997 |      54060
SPHINCS+-SHA2-192s-simple            |            |                |                 |            |                           |           
keypair                              |          4 |          3.854 |      963483.500 |   1377.088 |                 963483008 |    1377041
sign                                 |          1 |          8.952 |     8952222.000 |      0.000 |                8952221696 |          0
verify                               |        393 |          3.005 |        7646.824 |     22.087 |                   7646619 |      22094
SPHINCS+-SHA2-256f-simple            |            |                |                 |            |                           |           
keypair                              |         80 |          3.036 |       37949.288 |    135.687 |                  37949008 |     135586
sign                                 |          4 |          3.154 |      788423.750 |    758.504 |                 788422464 |     758664
verify                               |        147 |          3.000 |       20408.857 |     78.477 |                  20408599 |      78487
SPHINCS+-SHA2-256s-simple            |            |                |                 |            |                           |           
keypair                              |          5 |          3.063 |      612601.600 |   1181.531 |                 612600781 |    1181527
sign                                 |          1 |          7.778 |     7777613.000 |      0.000 |                7777612544 |          0
verify                               |        290 |          3.005 |       10361.672 |     38.680 |                  10361443 |      38610
SPHINCS+-SHAKE-128f-simple           |            |                |                 |            |                           |           
keypair                              |        214 |          3.011 |       14069.355 |     18.949 |                  14069136 |      18942
sign                                 |         10 |          3.291 |      329125.000 |    102.840 |                 329124557 |     102950
verify                               |        154 |          3.011 |       19554.727 |     26.283 |                  19554487 |      26268
SPHINCS+-SHAKE-128s-simple           |            |                |                 |            |                           |           
keypair                              |          4 |          3.473 |      868218.500 |   2695.265 |                 868218240 |    2694852
sign                                 |          1 |          6.589 |     6588700.000 |      0.000 |                6588698624 |          0
verify                               |        451 |          3.005 |        6663.016 |     14.004 |                   6662791 |      14008
SPHINCS+-SHAKE-192f-simple           |            |                |                 |            |                           |           
keypair                              |        146 |          3.015 |       20650.904 |     68.108 |                  20650380 |      67506
sign                                 |          6 |          3.210 |      534941.833 |    340.162 |                 534941355 |     339890
verify                               |        104 |          3.015 |       28992.240 |    217.171 |                  28991983 |     217113
SPHINCS+-SHAKE-192s-simple           |            |                |                 |            |                           |           
keypair                              |          3 |          3.855 |     1284858.667 |    915.265 |                1284857941 |     915027
sign                                 |          1 |         11.588 |    11587693.000 |      0.000 |               11587692800 |          0
verify                               |        329 |          3.003 |        9128.182 |     25.131 |                   9127988 |      25117
SPHINCS+-SHAKE-256f-simple           |            |                |                 |            |                           |           
keypair                              |         54 |          3.015 |       55839.259 |     19.941 |                  55839057 |      19869
sign                                 |          3 |          3.401 |     1133733.667 |   8606.379 |                1133733291 |    8606511
verify                               |        101 |          3.001 |       29714.693 |    113.474 |                  29714445 |     113514
SPHINCS+-SHAKE-256s-simple           |            |                |                 |            |                           |           
keypair                              |          4 |          3.640 |      909944.500 |   2760.425 |                 909943872 |    2760677
sign                                 |          1 |         10.813 |    10813492.000 |      0.000 |               10813491968 |          0
verify                               |        203 |          3.010 |       14829.369 |     31.186 |                  14829163 |      31251
MAYO-1                               |            |                |                 |            |                           |           
keypair                              |       2409 |          3.001 |        1245.545 |      6.601 |                   1245358 |       6601
sign                                 |        840 |          3.000 |        3571.955 |     14.675 |                   3571724 |      14656
verify                               |       4037 |          3.000 |         743.209 |     60.349 |                    742968 |      60284
MAYO-2                               |            |                |                 |            |                           |           
keypair                              |        853 |          3.001 |        3518.517 |     13.219 |                   3518324 |      13163
sign                                 |        568 |          3.004 |        5289.491 |     17.992 |                   5289243 |      17956
verify                               |       7008 |          3.000 |         428.116 |     10.864 |                    427906 |      10850
MAYO-3                               |            |                |                 |            |                           |           
keypair                              |        608 |          3.005 |        4941.765 |     45.897 |                   4941505 |      45767
sign                                 |        213 |          3.012 |       14139.146 |     74.380 |                  14138767 |      74260
verify                               |       1129 |          3.002 |        2659.005 |     98.468 |                   2658753 |      98391
MAYO-5                               |            |                |                 |            |                           |           
keypair                              |        216 |          3.014 |       13952.384 |     84.502 |                  13951730 |      84420
sign                                 |         77 |          3.013 |       39132.844 |    387.247 |                  39132130 |     387279
verify                               |        406 |          3.000 |        7389.372 |    470.592 |                   7388736 |     470569
cross-rsdp-128-balanced              |            |                |                 |            |                           |           
keypair                              |      29397 |          3.000 |         102.052 |      4.443 |                    101876 |       4426
sign                                 |        351 |          3.003 |        8555.746 |     62.262 |                   8555278 |      62145
verify                               |        673 |          3.004 |        4463.053 |     34.205 |                   4462861 |      34106
cross-rsdp-128-fast                  |            |                |                 |            |                           |           
keypair                              |      29324 |          3.000 |         102.307 |      4.848 |                    102137 |       4829
sign                                 |        626 |          3.004 |        4798.690 |    129.754 |                   4798327 |     129602
verify                               |       1085 |          3.001 |        2766.330 |     75.441 |                   2765991 |      75256
cross-rsdp-128-small                 |            |                |                 |            |                           |           
keypair                              |      29362 |          3.000 |         102.176 |      4.543 |                    102003 |       4521
sign                                 |         89 |          3.001 |       33714.337 |    846.153 |                  33713514 |     846078
verify                               |        181 |          3.003 |       16592.586 |    400.500 |                  16591906 |     400409
cross-rsdp-192-balanced              |            |                |                 |            |                           |           
keypair                              |      13729 |          3.000 |         218.525 |     11.386 |                    218340 |      11362
sign                                 |        149 |          3.005 |       20169.389 |     45.118 |                  20168761 |      45130
verify                               |        303 |          3.003 |        9910.109 |    264.170 |                   9909458 |     264074
cross-rsdp-192-fast                  |            |                |                 |            |                           |           
keypair                              |      13926 |          3.000 |         215.434 |      5.415 |                    215256 |       5394
sign                                 |        268 |          3.006 |       11217.168 |    137.024 |                  11216692 |     136968
verify                               |        480 |          3.002 |        6254.398 |     29.901 |                   6254179 |      29861
cross-rsdp-192-small                 |            |                |                 |            |                           |           
keypair                              |      13951 |          3.000 |         215.041 |      4.705 |                    214870 |       4679
sign                                 |         64 |          3.029 |       47320.438 |    104.818 |                  47319748 |     104751
verify                               |        141 |          3.012 |       21361.617 |    209.302 |                  21361085 |     209264
cross-rsdp-256-balanced              |            |                |                 |            |                           |           
keypair                              |       8207 |          3.000 |         365.547 |      4.901 |                    365368 |       4883
sign                                 |         84 |          3.015 |       35898.583 |     47.744 |                  35897859 |      47788
verify                               |        191 |          3.012 |       15770.429 |     51.918 |                  15769942 |      51870
cross-rsdp-256-fast                  |            |                |                 |            |                           |           
keypair                              |       8198 |          3.000 |         365.966 |      7.500 |                    365788 |       7491
sign                                 |        137 |          3.017 |       22020.139 |     61.026 |                  22019406 |      60989
verify                               |        250 |          3.004 |       12015.232 |     71.351 |                  12014755 |      71283
cross-rsdp-256-small                 |            |                |                 |            |                           |           
keypair                              |       8207 |          3.000 |         365.564 |      4.515 |                    365382 |       4499
sign                                 |         44 |          3.033 |       68926.386 |    220.429 |                  68925772 |     220438
verify                               |        108 |          3.028 |       28036.806 |     38.835 |                  28036264 |      38758
cross-rsdpg-128-balanced             |            |                |                 |            |                           |           
keypair                              |      51316 |          3.000 |          58.462 |      3.219 |                     58289 |       3194
sign                                 |        382 |          3.005 |        7866.513 |     42.917 |                   7866168 |      42882
verify                               |        790 |          3.001 |        3798.156 |     64.900 |                   3797926 |      64815
cross-rsdpg-128-fast                 |            |                |                 |            |                           |           
keypair                              |      51279 |          3.000 |          58.504 |      3.417 |                     58329 |       3386
sign                                 |        746 |          3.003 |        4025.945 |     24.502 |                   4025723 |      24508
verify                               |       1283 |          3.002 |        2340.012 |     26.738 |                   2339816 |      26719
cross-rsdpg-128-small                |            |                |                 |            |                           |           
keypair                              |      51289 |          3.000 |          58.492 |      3.950 |                     58322 |       3927
sign                                 |        109 |          3.024 |       27745.110 |     65.052 |                  27744463 |      65068
verify                               |        234 |          3.004 |       12836.859 |     56.198 |                  12836368 |      56149
cross-rsdpg-192-balanced             |            |                |                 |            |                           |           
keypair                              |      30175 |          3.000 |          99.422 |      4.059 |                     99243 |       4038
sign                                 |        350 |          3.002 |        8575.789 |    114.515 |                   8575187 |     114424
verify                               |        603 |          3.001 |        4976.836 |     34.767 |                   4976587 |      34761
cross-rsdpg-192-fast                 |            |                |                 |            |                           |           
keypair                              |      30281 |          3.000 |          99.074 |      3.896 |                     98892 |       3870
sign                                 |        469 |          3.003 |        6402.810 |     99.742 |                   6402466 |      99662
verify                               |        758 |          3.002 |        3960.927 |     35.891 |                   3960724 |      35865
cross-rsdpg-192-small                |            |                |                 |            |                           |           
keypair                              |      30131 |          3.000 |          99.567 |      3.971 |                     99390 |       3945
sign                                 |         98 |          3.016 |       30779.204 |     62.172 |                  30778514 |      62205
verify                               |        158 |          3.008 |       19040.456 |    180.348 |                  19039937 |     180357
cross-rsdpg-256-balanced             |            |                |                 |            |                           |           
keypair                              |      19692 |          3.000 |         152.347 |      3.473 |                    152171 |       3448
sign                                 |        196 |          3.000 |       15306.806 |     37.281 |                  15306244 |      37244
verify                               |        323 |          3.008 |        9312.824 |     49.256 |                   9312526 |      49261
cross-rsdpg-256-fast                 |            |                |                 |            |                           |           
keypair                              |      19788 |          3.000 |         151.614 |      3.913 |                    151437 |       3888
sign                                 |        259 |          3.009 |       11617.838 |    151.351 |                  11617272 |     151306
verify                               |        413 |          3.004 |        7273.676 |     54.080 |                   7273461 |      54019
cross-rsdpg-256-small                |            |                |                 |            |                           |           
keypair                              |      19727 |          3.000 |         152.081 |      3.349 |                    151893 |       3329
sign                                 |         71 |          3.039 |       42808.225 |     74.579 |                  42807534 |      74623
verify                               |        122 |          3.017 |       24733.238 |    115.012 |                  24732483 |     114959
Ended at 2024-09-13 23:46:45o
```

## Maintainer

Alex J Lennon <ajlennon@dynamicdevices.co.uk>

## Licensing

Note that this repository is licensed under the MIT license.

`libOQS` is also licensed under the MIT license but sub-components are licensed under other licenses. For further details on this please see [here](https://openquantumsafe.org/liboqs/license.html)
