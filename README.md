
# sedenv

reads from stdin and writes to stdout, turns __SOME_TEXT__ into whatever env var $SOME_TEXT is set to.

Useful in Kubernetes to create config files in entrypoint.sh from env vars, if the program won't accept them.

Written in C++ to remove need for runtime dependencies. binary can just be copied into a docker image.

# compile and build

the binary (linux x86_64) already in git repo and ready to use. other wise g++ and make are required to build from source.
