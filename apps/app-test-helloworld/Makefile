# /apps/appname/Makefile
# 定义根目录以及库目录
UK_ROOT ?= $(PWD)/../../unikraft
UK_LIBS ?= $(PWD)/../../libs
# 定义需要用到的各类库
LIBS := $(UK_LIBS)/lib-headers:$(UK_LIBS)/intel-intrinsics:$(UK_LIBS)/musl:$(UK_LIBS)/uk-dpdk
# 嵌套执行根目录文件夹中的 Makefile。
all:
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS)

$(MAKECMDGOALS):
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS) $(MAKECMDGOALS)