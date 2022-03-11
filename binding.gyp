{
    "targets": [
        {
            "target_name": "cpuminer",
            "sources": [
                "cpp/addon.cc",
                "cpp/cpuminer.cpp",
                "cpp/solver.cpp",
                "cpp/balloon.cpp",
                "cpp/sha3.c"
            ],
            'cflags_cc+': [ '-march=native', '-O3', '-std=c++17' ],
            "include_dirs": ["<!(node -e \"require('nan')\")"]
        }
    ]
}