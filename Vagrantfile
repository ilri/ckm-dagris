# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|

  config.vm.box = "ubuntu/trusty32"
  #config.vm.box_url = "http://files.vagrantup.com/precise32.box"

  config.hostmanager.enabled = true
  config.hostmanager.manage_host = true
  config.vm.define "dagris" do |node|
    node.vm.hostname = "dagris.local"
    node.vm.network :private_network, ip: "172.22.22.26"
    node.hostmanager.aliases = [
      "ago.dagris.local", # Angola
      "gab.dagris.local", # Gabon
      "cmr.dagris.local", # Cameroon
      "nga.dagris.local", # Nigeria
      "civ.dagris.local", # Côte d'Ivoire
      "gha.dagris.local", # Ghana
      "sen.dagris.local", # Senegal
      "mar.dagris.local", # Morocco
      "tun.dagris.local", # Tunisia
      "sdn.dagris.local", # Sudan
      "eth.dagris.local", # Ethiopia
      "cod.dagris.local", # DR Congo
      "uga.dagris.local", # Uganda
      "ken.dagris.local", # Kenya
      "mwi.dagris.local", # Malawi
      "zwe.dagris.local", # Zimbabwe
      "kor.dagris.local", # Korea
      "dagris.local"      # Global
     ]
  end
  config.vm.provision :hostmanager

  config.vm.synced_folder ".", "/var/www/html/dagris/"

  config.vm.provider "virtualbox" do |vm|
    vm.customize ["modifyvm", :id, "--memory", "4096"]
    vm.customize ["modifyvm", :id, "--cpus", "1"]
    vm.customize ["modifyvm", :id, "--cpuexecutioncap", "85"]
  end

  config.vm.provision "shell" do |script|
    script.path = "provisioner.sh"
  end


end
