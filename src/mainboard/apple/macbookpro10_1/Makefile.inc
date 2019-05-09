romstage-y += gpio.c
romstage-y += early_init.c

bootblock-y += gpio.c
bootblock-y += early_init.c

cbfs-files-y += spd.bin
spd.bin-file := spd.bin
spd.bin-type := spd

ramstage-$(CONFIG_MAINBOARD_USE_LIBGFXINIT) += gma-mainboard.ads
