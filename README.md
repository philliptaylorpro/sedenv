
# sedenv

reads from stdin and writes to stdout, turns \_\_SOME\_TEXT\_\_ into whatever env var $SOME\_TEXT is set to.

Useful in Kubernetes to create config files in entrypoint.sh from env vars, if the program won't accept them.

Written in C++ to remove need for runtime dependencies. binary can just be copied into a docker image.

https://github.com/philliptaylorpro/sedenv

# example usage in Kubernetes

In your docker file

```Dockerfile
COPY entrypoint.sh /app/entrypoint.sh
COPY monstache-template.toml /app/monstache-template.toml
COPY sedenv /app/sedenv

ENTRYPOINT /app/entrypoint.sh
```

In your entrypoint script

```bash
sedenv < /app/monstache-template.toml > /app/monstache.toml
monstache -f /monstache-conf/monstache.toml --replay
```

Now you ensure your Kubernetes `deployment.yaml` environmental variables can be written into your configs.

# compile and build

the binary (linux x86_64) already in git repo and ready to use.

Otherwise you need `g++` and `make` available.

# license

This is GPLv2
