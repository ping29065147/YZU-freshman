var state = ["Alabama","Alaska","Arizona","Arkansas","California",
"Colorado","Connecticut","Delaware","Florida","Georgia",
"Hawaii","Idaho","Illinois","Indiana","Iowa",
"Kansas","Kentucky","Louisiana","Maine","Maryland",
"Massachusetts","Michigan","Minnesota","Mississippi","Missouri",
"Montana","Nebraska","Nevada","New Hampshire","New Jersey",
"New Mexico","New York","North Carolina","North Dakota","Ohio",
"Oklahoma","Oregon","Pennsylvania","Rhode Island","South Carolina",
"South Dakota","Tennessee","Texas","Utah","Vermont",
"Virginia","Washington","WestVirginia","Wisconsin","Wyoming"];
var height=[2.291288,3.834058,3.929377,6.236986,6.637771,7.355270,8.027453,
8.537564,10.860018,11.456439,12.424975,12.614278,12.775367,13.044922,
13.297368,13.349157,13.896043,14.501034,15.407790,15.454449,15.630099,
15.890249,16.976749,18.264994,19.437592,19.904271,21.167192,22.366046,
22.766642,24.894377,25.093027,28.635118,29.250641,31.477135,31.620405,
32.718802,36.734861,36.847931,38.527912,41.487950,48.725148,53.593376,
57.271022,64.993615,68.762272,87.326342,102.861557,168.611417,293.622751];
var merge =[
[-15,-29],
[-17,-26],
[-14,-16],
[-13,-32],
[-35,-44],
[-36,-46],
[-7,-38],
[-19,-41],
[-49,1],
[-21,-30],
[-37,6],
[-4,-42],
[-48,8],
[-34,-45],
[-22,-28],
[-27,2],
[-3,-31],
[-6,-43],
[-12,3],
[-1,-18],
[-50,11],
[-20,17],
[-8,20],
[5,7],
[-23,9],
[16,19],
[-24,-40],
[4,15],
[-47,10],
[-25,12],
[-10,18],
[-2,27],
[21,29],
[24,26],
[-11,25],
[-5,28],
[30,31],
[-39,33],
[-9,-33],
[13,14],
[23,32],
[22,36],
[35,40],
[41,42],
[37,38],
[34,43],
[39,44],
[45,46],
[47,48]];

function Node(value, height) {
  this.value = value;		//州名
  this.height = height;		//node高度
  this.up_level = null;		//node的上一層
  this.check = 0;
  this.left = null;
  this.right = null;
}

var rank_array = new Array(49);
var result_array = new Array(49);
var result_array_counter = 0;

function StateTree() {
  this.root = null;
}

StateTree.prototype.push = function(i, i1, i2) {
	
	/*i、i1、i2 關係圖
	
		i
	   / \
	  i1 i2
	  
	*/
	
  var i_node = new Node(0, height[i]);
  rank_array[i] = i_node;
  
  if (i1 < 0) {
	  i1 *= -1;
	  var i1_node = new Node(state[i1-1], 0);		//如果左下為州則建立新node
  }  
  else {
	  var i1_node = rank_array[i1-1];		//已存在node
  }

  if (i2 < 0) {
	  i2 *= -1;
	  var i2_node = new Node(state[i2-1], 0);		//如果右下為州新node
  }
  else {
	  var i2_node = rank_array[i2-1];		//已存在node
  }
  
  i1_node.up_level = i_node;		//連結上一層
  i2_node.up_level = i_node;
  i_node.left = i1_node;		//連結下一層
  i_node.right = i2_node;

};

function result_traverse(node, dis, current_dis, target_city, current_check) {

  
  if (!node || dis<current_dis) return;		//如果為node或dis超過則返回

  let currentNode = node;


  if (currentNode.check > 0){		//如果check>0 則為已走過路徑
	  current_dis -= 1;
	  current_check = currentNode.check;		//將目前check儲存
  }
  else
	  current_dis += 1;
  
  result_traverse(currentNode.left, dis, current_dis, target_city, current_check);		//與find_node進行類似工作
  result_traverse(currentNode.right, dis, current_dis, target_city, current_check);
  if (currentNode.value != 0 && currentNode.value != target_city && current_check<=50){
	 result_array[result_array_counter] = currentNode.value;		//將(州節點&&非目標州&&height<50)之州存入陣列
	 result_array_counter++;
  }
}

function get_result(node, dis, target_city){
	
	var current_node = node;
	for(var counter=1; counter<dis; counter++){
		
		current_node = current_node.up_level;		//從目標州找到dis-1層node
		if (!(counter==dis-1)){
			current_node.check = current_node.height;		//將高度寫入各層node
		}
	}
	
	result_traverse(current_node, dis, dis-1, target_city, current_node.check);		//尋找所有符合條件的州(從dis-1開始)
}

function find_node(node, target_city, dis){
	
	if (!node) return;		//NULL則返回 (*1)
	
	let currentNode = node;
	
	find_node(currentNode.left, target_city, dis);		//往左找下一個 (*2)
	find_node(currentNode.right, target_city, dis);		//往右找下一個 (*3)
	
	/*範例
			A
		   / \
		  B   C
		 / \
		D   E
		
		從A開始尋找
		*2 找到B
			*2 找到D
				*2 找到NULL  *1 返回D
				*3 找到NULL  *1 返回D  *1 返回B
			*3 找到E
				*2 找到NULL  *1 返回E
				*3 找到NULL  *1 返回E  *1 返回B  *1 返回A
		*3 找到C
			*2 找到NULL  *1 返回C
			*3 找到NULL  *1 返回C  *1 返回A  *1 結束
		
	*/
	
	if (currentNode.value === target_city){
		get_result(currentNode, dis, target_city);
	}
}

function progress(){
	var dis = document.form.dis.value;
	var target = document.form.target.value;
	var output=""

    /*----------------- Your Code Start-------------*/
	
	let tree = new StateTree();		//建立空的tree

	for(var i=0; i<49; i++){
		var i1 = merge[i][0];
		var i2 = merge[i][1];
		tree.push(i, i1, i2);		//將資料以樹狀結構連結
	}

	find_node(rank_array[48], target, dis);		//尋找目標州(從頂層開始)
	result_array.sort();
	for(var i=0; i<result_array_counter; i++){
		output += result_array[i];
		if (i != result_array_counter-1)
			output += ", ";
	}

    /*----------------- Your Code End --------------*/
    document.getElementById('out').innerHTML= output;
}