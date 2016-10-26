# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/trusty32"
  config.vm.box_check_update = false
  config.vm.provision "shell", inline: <<-SHELL
    apt-get update
    apt-get install -y nasm
  SHELL
end
