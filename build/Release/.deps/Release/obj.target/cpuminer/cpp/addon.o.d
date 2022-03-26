cmd_Release/obj.target/cpuminer/cpp/addon.o := g++ '-DNODE_GYP_MODULE_NAME=cpuminer' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-DV8_DEPRECATION_WARNINGS' '-DV8_IMMINENT_DEPRECATION_WARNINGS' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-D__STDC_FORMAT_MACROS' '-DOPENSSL_NO_PINSHARED' '-DOPENSSL_THREADS' '-DBUILDING_NODE_EXTENSION' -I/home/jinwoolim/.cache/node-gyp/14.19.0/include/node -I/home/jinwoolim/.cache/node-gyp/14.19.0/src -I/home/jinwoolim/.cache/node-gyp/14.19.0/deps/openssl/config -I/home/jinwoolim/.cache/node-gyp/14.19.0/deps/openssl/openssl/include -I/home/jinwoolim/.cache/node-gyp/14.19.0/deps/uv/include -I/home/jinwoolim/.cache/node-gyp/14.19.0/deps/zlib -I/home/jinwoolim/.cache/node-gyp/14.19.0/deps/v8/include -I../node_modules/nan  -fPIC -pthread -Wall -Wextra -Wno-unused-parameter -m64 -O3 -fno-omit-frame-pointer -march=native -O3 -std=c++17 -fno-rtti -fno-exceptions -std=gnu++1y -MMD -MF ./Release/.deps/Release/obj.target/cpuminer/cpp/addon.o.d.raw   -c -o Release/obj.target/cpuminer/cpp/addon.o ../cpp/addon.cc
Release/obj.target/cpuminer/cpp/addon.o: ../cpp/addon.cc \
 ../node_modules/nan/nan.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node_version.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/errno.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/version.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/unix.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/threadpool.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/linux.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/cppgc/common.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8config.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8-internal.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8-version.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8config.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8-platform.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node_version.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node_buffer.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node_object_wrap.h \
 ../node_modules/nan/nan_callbacks.h \
 ../node_modules/nan/nan_callbacks_12_inl.h \
 ../node_modules/nan/nan_maybe_43_inl.h \
 ../node_modules/nan/nan_converters.h \
 ../node_modules/nan/nan_converters_43_inl.h \
 ../node_modules/nan/nan_new.h \
 ../node_modules/nan/nan_implementation_12_inl.h \
 ../node_modules/nan/nan_persistent_12_inl.h \
 ../node_modules/nan/nan_weak.h ../node_modules/nan/nan_object_wrap.h \
 ../node_modules/nan/nan_private.h \
 ../node_modules/nan/nan_typedarray_contents.h \
 ../node_modules/nan/nan_json.h ../node_modules/nan/nan_scriptorigin.h \
 ../cpp/cpuminer.h ../cpp/solver.h ../cpp/balloon.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/sha.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/e_os2.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/opensslconf.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/./opensslconf_asm.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/././archs/linux-x86_64/asm/include/openssl/opensslconf.h \
 /home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/opensslv.h
../cpp/addon.cc:
../node_modules/nan/nan.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node_version.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/errno.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/version.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/unix.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/threadpool.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/uv/linux.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/cppgc/common.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8config.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8-internal.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8-version.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8config.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/v8-platform.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node_version.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node_buffer.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/node_object_wrap.h:
../node_modules/nan/nan_callbacks.h:
../node_modules/nan/nan_callbacks_12_inl.h:
../node_modules/nan/nan_maybe_43_inl.h:
../node_modules/nan/nan_converters.h:
../node_modules/nan/nan_converters_43_inl.h:
../node_modules/nan/nan_new.h:
../node_modules/nan/nan_implementation_12_inl.h:
../node_modules/nan/nan_persistent_12_inl.h:
../node_modules/nan/nan_weak.h:
../node_modules/nan/nan_object_wrap.h:
../node_modules/nan/nan_private.h:
../node_modules/nan/nan_typedarray_contents.h:
../node_modules/nan/nan_json.h:
../node_modules/nan/nan_scriptorigin.h:
../cpp/cpuminer.h:
../cpp/solver.h:
../cpp/balloon.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/sha.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/e_os2.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/opensslconf.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/./opensslconf_asm.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/././archs/linux-x86_64/asm/include/openssl/opensslconf.h:
/home/jinwoolim/.cache/node-gyp/14.19.0/include/node/openssl/opensslv.h:
