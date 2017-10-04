# This app.py is by GesVM
# JAPeTo <jeffersonamado@gmail.com>
# AlexRedondos

from flask import (Flask, jsonify, request)
import subprocess
app = Flask(__name__)
@app.route('/')
def api_root():
    """
    Welcome message
    :return: json message
    """
    return jsonify({"message": 'Welcome - help by usage'})

@app.route('/help')
def api_help():
    """
    help message
    :return: json message
    """
    return jsonify({"home": "http://localhost:5000/ (GET)",
                    "ostypes":"http://localhost:5000/vms/ostypes (GET)",
                    "vms GET":"http://localhost:5000/vms (GET)",
                    "running":"http://localhost:5000/vms/running (GET)",
                    "info":"http://localhost:5000/vms/info/vmname (GET)",
                    "vms POST":"http://localhost:5000/vms (POST)",
                    "vmname":"http://localhost:5000/vms/vmname (DELETE)"})

@app.route("/vms", methods=['GET'])
def vms_list():
    """
    Allow obtain list of machines created
    :return: json with array value
    """
    out = subprocess.Popen("VBoxManage list vms",
                           shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    vms = []
    for line in out.stdout.readlines():
        line = str(line.decode("utf-8").replace("\n", "").replace("\"", ""))
        if len(line.split(" ")) > 1:
            vms.append(line.replace("\n", ""))
    return jsonify(vms = vms) # { vms = [{},..{}] }

@app.route("/vms/running", methods=['GET'])
def vms_running ():
    """
    Allow return all running machines
    :return: json 
    """
    out = subprocess.Popen("VBoxManage list runningvms",
                           shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    vms = []
    for line in out.stdout.readlines():
        line = str(line.decode("utf-8").replace("\n", "").replace("\"", ""))
        if len(line.split(" ")) > 1:
            vms.append(line.replace("\n", ""))
    return jsonify(vms = vms) # { vms = [{},..{}] }

@app.route("/vms/info/<string:vmname>", methods=['GET'])
def vms_info(vmname):
    """
    Allow obtain machine info according to name
    :param vmname: machine name
    :return: json with array 
    """
    out = subprocess.Popen("VBoxManage showvminfo {}".format(vmname),
                           shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    vms = []
    for line in out.stdout.readlines():
        line = str(line.decode("utf-8").replace("\n", ""))
        vms.append(line)
    return jsonify(vm = vms)# { vms = [{},..{}] }

@app.route("/vms/<vmname>/mem/<mem>/ostype/<ostype>/cpu/<cpu>", methods=['POST'])
def vms_post(vmname, mem, ostype, cpu):
    """
    Allow create a new machine
    :param vmname: name 
    :param mem: quantity memory
    :param ostype: type os
    :param cpu: quantity processors
    :return: json status message
    """
    try:
        out = subprocess.Popen("VBoxManage createvm --name {} --register".format(vmname), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out = subprocess.Popen("VBoxManage modifyvm {} --memory {} --acpi on".format(vmname, mem), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out = subprocess.Popen("VBoxManage modifyvm {} --nic1 bridged --bridgeadapter1 eth0".format(vmname), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out = subprocess.Popen("VBoxManage modifyvm {} --ostype {} --cpus {}".format(vmname, ostype, cpu), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        return jsonify({"message":" sucessfully"})
    except Exception as e:
        return jsonify({"message": " :( No create {}".format(vmname)})

@app.route("/vms/api", methods=['POST'])
def vms_post_request():
    """
    Allow create a machine from json data
    curl -d "@data.json" -H "Content-Type: application/json" -X POST http://localhost:5000/vms/api 
    :return: json status code
    """
    try:
        vmname = request.json['vmname']
        ostype = request.json['ostype']
        mem = request.json['mem']
        cpu = request.json['cpu']

        out = subprocess.Popen("VBoxManage createvm --name {} --register".format(vmname), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out = subprocess.Popen("VBoxManage modifyvm {} --memory {} --acpi on".format(vmname, mem), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out = subprocess.Popen("VBoxManage modifyvm {} --nic1 bridged --bridgeadapter1 eth0".format(vmname), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out = subprocess.Popen("VBoxManage modifyvm {} --ostype {} --cpus {}".format(vmname, ostype, cpu), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        return jsonify({"message":" sucessfully"})
    except Exception as e:
        return jsonify({"message": " :( error"})

@app.route("/vms/", methods=['POST'])
def vms_post_file():
    """
    Allow create a machine from json data 
    :return: json status code
    """
    try:
        vmname = request.json['vmname']
        ostype = request.json['ostype']
        mem = request.json['mem']
        cpu = request.json['cpu']
        out = subprocess.Popen("./vmscript.sh createnode {} {} {}".format(vmname, mem, cpu),
                               shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        return jsonify({"message":" sucessfully"})
    except Exception as e:
        return jsonify({"message": " :( error"})

@app.route("/vms/<string:vmname>", methods=['DELETE'])
def vms_del(vmname):
    """
    Allow delete a machine according to name
    :param vmname: virtual machine name 
    :return: json status message
    """
    try:
        out = subprocess.Popen("VBoxManage controlvm {} poweroff".format(vmname),
                           shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        out = subprocess.Popen("VBoxManage unregistervm {} --delete".format(vmname),
                           shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        return jsonify({"message": " sucessfully delete {}".format(vmname)})
    except Exception as e:
        return jsonify({"message": " :( No delete {}".format(vmname)})

@app.route("/vms/ostypes", methods=['GET'])
def ostypes():
    """
    Return all ostypes support by virtualbox version
    :return: return json
    """
    out = subprocess.Popen("VBoxManage list ostypes",
                           shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    vms = {}; oskey = ""; os = {}
    for line in out.stdout.readlines():
        line = str(line.decode("utf-8").replace("\n", ""))
        if len(line.split(":")) > 1:
            key = line.split(":")[0]; value = str.strip(line.split(":")[1])
            os[key] = value
            if key=="ID": oskey = value
        else:
            vms[oskey] = os
            os = {}
    return jsonify(vms = vms)# { vms = [{},..{}] }

app.debug = True
app.run(host='0.0.0.0')
