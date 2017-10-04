#!/bin/bash
# GNU bash, version 4.3.46
# Manage the VirtualBox with command line tools
# vboxmanage.
#
# Usage: `vbox help`
# by JAPeTo
# Jefferson Amado pena

function usage()
{
    cat <<END
    Usage: $(basename $0) (ostypes|createvm|createnode|createvm_ram_cpu|on|off|restore|snapshot|help)
Commands:
	ostypes			List of the OS types VirtualBox recognises.
				<Match name>

	createvm		Create a default vm
				<VM name>

	createnode		Create a full node vm
				<VM name>

	createvm_ram_cpu	Create a full node vm
				<VM name> <RAM> <CPU>

	on          	    	Turn on a VM. 
				<VM name>

	off         	    	Turn off a VM.
				<VM name>

	list        	    	List VMs.
				<VM name>

	restore     	   	 Restore a VM to a snapshot.
				<VM name> <snapshot name>

	snapshot        	Take a snapshot of the VM.
				<VM name> <snapshot name>

	deletevm		Delete a VM
				<VM name>

	help            	Print this menu.
END
}

function main()
{
    ACTION=$1
    case $ACTION in
		ostypes)
		vbox_ostypes "$2"
		;;
		createvm)
		vbox_createvm "$2"
		;;
		createnode_one)
		vbox_createnode2 "$2"
		;;
		createnode)
		vbox_createnode "$2" "$3" "$4"
		;;
		on)
		vbox_on "$2"
		;;
		off)
		vbox_off "$2"
		;;
		list)
		vbox_list
		;;
		restore)
		vbox_restore "$2" "$3"
		;;
		snapshot)
		vbox_snapshot "$2" "$3"
		;;
		deletevm)
		vbox_deletevm "$2"
		;;
		help)
		usage
		;;
		*)
		usage
		;;
    esac
}


function vbox_ostypes()
{
    OSMATCH="$1"
	VBoxManage list ostypes | grep "$OSMATCH"
}

function vbox_createvm()
{
    VMNAME="$1"
	VBoxManage createvm --name $VMNAME --ostype "Ubuntu_64" --register
}

function vbox_createnod2()
{
    VMNAME="$1"
	VBoxManage createvm --name "$VMNAME" --ostype Ubuntu_64 --register
	VBoxManage modifyvm "$VMNAME" --memory 768 --boot1 net --nic1 hostonly --hostonlyadapter1 vboxnet0  --boot2 disk --vram 12
	VBoxManage createhd --filename $VMNAME".vdi" --size 40000
	VBoxManage storageattach $VMNAME --storagectl "IDE Controller" --port 0 --device 0 --type hdd --medium $1".vdi"
	VBoxManage startvm $VMNAME
}

function vbox_createnode()
{
    VMNAME="$1"
	RAM="$2"
	CPU="$3"
	VBoxManage createvm --name "$VMNAME" --ostype Ubuntu_64 --register
	VBoxManage modifyvm "$VMNAME" --memory $RAM --cpus $CPU
	VBoxManage startvm $VMNAME
}

function vbox_deletevm()
{
    VMNAME="$1"
	VBoxManage controlvm $VMNAME poweroff
	sleep 5
	VBoxManage unregistervm $VMNAME --delete
}

function vbox_on()
{
    VMNAME="$1"
    vboxmanage startvm "$VMNAME"
}

function vbox_off()
{
    VMNAME="$1"
    vboxmanage controlvm "$VMNAME" poweroff
}

function vbox_list()
{
    echo "All VMs available:"
    vboxmanage list vms
    echo "VMs currently running:"
    vboxmanage list runningvms

}

function vbox_restore()
{
    VMNAME="$1"
    SNAPSHOT="$2"
    vboxmanage controlvm "$VMNAME" poweroff || echo "Didn't power off VM, it's probably off already"
    vboxmanage snapshot "$VMNAME" restore "$SNAPSHOT" || echo "Failed to restore snapshot"
}

function vbox_snapshot()
{
    VMNAME="$1"
    SNAPSHOT="$2"
    vboxmanage controlvm "$VMNAME" pause || echo "Failed to pause"
    vboxmanage snapshot "$VMNAME" take "$SNAPSHOT" || echo "Failed to take snapshot"
    vboxmanage controlvm "$VMNAME" resume || echo "Failed to resume"
}

main "$@"

