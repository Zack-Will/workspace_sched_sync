if [[ ! -d /mnt/huge1G ]]; then
  mkdir /mnt/huge1G
  mount -t hugetlbfs -o pagesize=1G none /mnt/huge1G
fi

sudo qemu-system-x86_64 \
-m 1024 \
-kernel build/app-test-helloworld_kvm-x86_64 \
-nodefaults \
-nographic \
-vga none \
--device sga \
-serial stdio \
--enable-kvm \
-smp cores=2 \
-enable-kvm \
-object memory-backend-file,id=mem,size=1G,mem-path=/mnt/huge1G/test,share=on \
-numa node,memdev=mem \
-mem-prealloc \
-chardev socket,id=char0,path=/home/libos/app-test-suit/vhost-net \
-netdev vhost-user,id=testtap1,chardev=char0,vhostforce \
-device virtio-net-pci,netdev=testtap1,rx_queue_size=1024,tx_queue_size=1024 \
-fsdev local,id=myid,path=subcorefs,security_model=none \
-device virtio-9p-pci,fsdev=myid,mount_tag=fs0 \
#> result.txt
