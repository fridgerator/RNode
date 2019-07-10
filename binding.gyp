{
  "targets": [
    {
      "target_name": "RNode",
      "sources": [
        "src/main.cpp",
        "src/thing.cpp"
      ],
      "variables": {
        'R_HOME%' : '<!(./r_tmp/R-3.4.3/bin/R RHOME)',
        'RCPPFLAGS%' : '<!(<(R_HOME%)/bin/R CMD config --cppflags | sed "s/^...//")',
        'RLDFLAGS%' : '<!(<(R_HOME%)/bin/R CMD config --ldflags)',
        'RBLAS%' : '<!(<(R_HOME%)/bin/R CMD config BLAS_LIBS)',
        'RLAPACK%' : '<!(<(R_HOME%)/bin/R CMD config LAPACK_LIBS)',
        'RCPPINCL%' : '<!(echo "Rcpp:::CxxFlags()" | <(R_HOME%)/bin/R --vanilla --slave | sed "s/^...//")',
        'RCPPLIBS%' : '<!(echo "Rcpp:::LdFlags()" | <(R_HOME%)/bin/R --vanilla --slave)',
        'RINSIDEINCL%' : '<!(echo "RInside:::CxxFlags()" | <(R_HOME%)/bin/R --vanilla --slave | sed "s/^...//")',
        'RINSIDELIBS%' : '<!(echo "RInside:::LdFlags()" | <(R_HOME%)/bin/R --vanilla --slave)',
      },
      'conditions': [
        ['OS=="mac"', {
          "cflags!": [ '-fno-rtti', "-fno-exceptions" ],
          "cflags_cc!": [
            "-fno-rtti",
            "-fno-exceptions"
          ],
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            "GCC_ENABLE_CPP_RTTI": 'YES'
          },
          "include_dirs": [
            "<!(node -e \"require('nan')\")",
            '/<(RCPPFLAGS)',
            '/<(RCPPINCL)',
            '/<(RINSIDEINCL)'
          ],
          "libraries": [
            '<(RLDFLAGS)',
            '<(RCPPLIBS)',
            '<(RINSIDELIBS)',
            '<(RBLAS)',
            '<(RLAPACK)'
          ]
        }]
      ]
    }
  ]
}
