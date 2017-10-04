# -*- mode: ruby -*-
# # vi: set ft=ruby :
#
Vagrant.configure("2") do |config|
  config.vm.define "apache2" do |apache2|
    apache2.vm.box = "ubuntu/xenial64"
    apache2.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--memory', '386' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
      vb.customize [ 'modifyvm', :id, '--name', 'apache2' ]
    end
    apache2.vm.network "forwarded_port", guest: 80, host: 8081
    apache2.vm.provision "shell", path: "apache2_install.sh"
  end
  config.vm.define "psql" do |psql|
    psql.vm.box = "ubuntu/trusty64"
    psql.vm.provider :virtualbox do |vb|
      vb.customize [ 'modifyvm', :id, '--memory', '512' ]
      vb.customize [ 'modifyvm', :id, '--cpus', '2' ]
      vb.customize [ 'modifyvm', :id, '--name', 'psql' ]
    end
    psql.vm.network "forwarded_port", guest: 5432, host: 5432
    psql.vm.provision "shell", path: "psql_install.sh"
  end
end
