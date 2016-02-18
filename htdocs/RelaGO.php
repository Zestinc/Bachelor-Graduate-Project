<?php 
$IdMode = 1;
$NameMode = 2;
$Go_NoneRela = "<br/><h3>相关的疾病</h3><br/><h3>相关的症状</h3>";
$Doid_NoneRela = "<br/><h3>相关的基因</h3><br/><h3>相关的症状</h3>";
$Doid2DoidNone = "<br/><h3> 具有相同症状的疾病（高相关->低相关）<h3/>";

function Name2Id($name, $table, $db){
	$sql = 'select * from ' . $table . ' where name = "' . $name . '"';
	$result = QuerySQL($db, $sql);
	$id = "";
	while($row = mysql_fetch_array($result)){
		$id = $row[$table . '_id'];
	}
	if($id == "")	return "@未收录";
	else 			return $id;
}

function QuerySQL($db, $sql)
{
	if(mysql_select_db($db)==false) exit("select db error");
	$result = mysql_query($sql);
	if($result == false) exit("query error!" . $sql);
	return $result;
}

function Id2Name($table, $id, $db){
	if(mysql_select_db($db)==false) exit("select db error");
	$sql = 'select * from ' . $table . ' where ' . $table . '_id = "' . $id . '"';
	$result = mysql_query($sql);
	if($result == false) exit("query error!" . $sql);
	while($row = mysql_fetch_array($result)){
		return $row['name'];
	}
}


function Doid2Gene($type, $id, $db){
	$ans = "<br/><h3>相关的基因</h3>";
	$name = Id2Name("doid", $id, "test");
	mysql_select_db("relationship");
	$sql = 'select * from disease2gene where disease = "' . $name . '"';
	$result = mysql_query($sql); 
	if($result == false) exit("query error!" . $sql);
	while($row = mysql_fetch_array($result)){
		$name = Id2Name("go", $row['go_id'], "go");
		// $ans = $ans . "hahahahahaha" . $name . "hehehe";
		$ans = $ans . '<p><a href="javascript:LayerPage(\''. $row['go_id'] . '\');">' . $row['go_id'] . ' ' . $name . '</a></p>';
	}
	return $ans;
}

function Doid2Symptom($type, $IdOrName, $db, $mode){
	$ans = "";
	if($mode == $GLOBALS['IdMode']){
		$ans = "<br/><h3>相关的症状</h3>";
		$name = Id2Name($type, $IdOrName, $db);
	}
	else 
		$name = $IdOrName;
	mysql_select_db("relationship");
	$sql = 'select * from disease2symptom where disease = "' . $name . '"';
	$result = mysql_query($sql);
	if($result == false) exit("query error!<br/>" . $sql);
	while($row = mysql_fetch_array($result)){
		$ans = $ans . '<p>' . $row['symptom'] . '</p>';
	}
	return $ans;
}

function GetDoidId($name){
	$ans = "<br/><h3>相关的疾病</h3>";
	foreach ($name as $key => $value) {
		$sql = 'select * from doid where name = "' . $value . '"';
		$result = QuerySQL("test", $sql);
		while($row = mysql_fetch_array($result)){
			$ans = $ans . '<p><a href="javascript:LayerPage(\''. $row['doid_id'] . '\');">' . $row['doid_id'] . ' ' . $value . '</a></p>';
		}
	}
	return $ans;
}

function Go2SymptomAndDoid($type, $id, $db){
	mysql_select_db("relationship");
	$sql = 'select * from disease2gene where go_id = "' . $id . '"';
	$result = mysql_query($sql);
	if($result == false) exit("query error!<br/" . $sql);
	$ans = "<br/><h3>相关的症状</h3>";
	$name = array();
	while($row = mysql_fetch_array($result)){
		array_push($name, $row['disease']);
		$ans = $ans . Doid2Symptom("doid", $row['disease'], "test", $GLOBALS['NameMode']);
	}
	$ans = GetDoidId($name) . $ans;
	return $ans;
}

//根据$id找到本体间相关的ID然后显示“超链接”
function RelaGO($con, $id, $type){
	if($type == "doid") $db = "test";
	else 				$db = $type;
	
	//$ans: 最终输出的链接们，先存起来，方便处理
	if($type == "doid"){
		$ans = Doid2Gene($type, $id, $db);
		$ans = $ans . Doid2Symptom($type, $id, $db, $GLOBALS['IdMode']);	
	}
	elseif($type == "go"){
		$ans = Go2SymptomAndDoid($type, $id, $db);
	}
	elseif($type == "envo"){
		$ans = "";
	}

	if($ans == $GLOBALS['Doid_NoneRela'] || $ans == $GLOBALS['Go_NoneRela'] || $ans == "")
		$ans = "<h3>无本体间的相关资料</h3>";
	echo($ans);
}

// function DupilicaRemove($x){
// 	sort($x);
// 	for ($i=1; $i < count($x); $i++) { 
// 		if($x[$i] == $x[$i - 1])
// 			unset($x[$i-1]);
// 	}
// 	return $x;
// }

function showArray($name, $x){
	foreach ($x as $key => $value) {
		echo($name);
		echo("key:" . $key . "->" . $value . "<br/>");
	}
}

// function Match($x, $y){
// 	$time = 0;
// 	foreach ($x as $xkey => $xvalue) {
// 		foreach ($y as $ykey => $yvalue) {
// 			if($xvalue == $yvalue){
// 				$time++;
// 				break;
// 			}
// 		}
// 	}
// 	return $time;
// }

function CountDuplicate($x){
	array_push($x, "zzzzzzzzzzzzzzz"); //增加排序后字典最后一项，用于将循环最后的节点加入到num中
	sort($x);
	$num = array();
	$count = 1;
	for ($i=1; $i < count($x); $i++) { 
		if($x[$i] == $x[$i-1]){
			$count++;
		}
		else {
			$num[$x[$i-1]] = $count;
			$count = 1;
		}
	}
	return $num;
}

function handlequote($x){
	if($x[0] == '"')
		$x = '\\' . $x;
	if($x[strlen($x)-1] == '"'){
		$x[strlen($x)-1] = '\\';
		$x[strlen($x)]   = '"';
	}
	return $x;
}

//离线版！ V2.0 分配
function Doid2Doid($con, $id){
	$ans = "<br/><h3> 具有相同症状的疾病（高相关->低相关）<h3/>";
	$name = Id2Name("doid", $id, "test");
	// $sql = 'select * from Doid2Doid where disease = "' . $name . '"';
	$sql = 'select * from Doid2Doid' . substr($name, 0, 1) . ' where disease = "' . $name . '" and counter > 2';
	$result = QuerySQL("relationship", $sql);
	$row = "";
	while ($row = mysql_fetch_array($result)) {
		$name = $row['relate_disease'];
		$id = Name2Id($name, "doid", "test");
		$count = $row['counter'];
		$ans = $ans . '<p><a href="javascript:LayerPage(\''. $id . '\');">' . $id . ' ' . $name. ' 相关病症个数：' . $count . '</a></p>';
	}
	if($ans == $GLOBALS['Doid2DoidNone'])
		$ans = "";
	echo($ans);
}

//疾病->症状->疾病 功能（几秒，待更新）
// function Doid2Doid($con, $id){
// 	echo("<br/><h3> 具有相同症状的疾病（高相关->低相关）<h3/>");
// 	//doid1->disease2symptom->symptom1(一对多)
// 	$name = Id2Name("doid", $id, "test");
// 	$sql = 'select * from disease2symptom where disease = "' . $name . '"';
// 	// echo("sql:" .$sql."<br/>");
// 	$result = QuerySQL("relationship", $sql);
// 	$symptom1 = array();
// 	for ($i=0; $row = mysql_fetch_array($result); $i++) { 
// 		$symptom1[$i] = $row['symptom'];
// 	}
// 	// showArray("symptom1", $symptom1);
// 	//symptom1->disease2symtpom->doid2(多对多) 
// 	$doid2name = array();
// 	$k = 0;
// 	for($i = 0; $i < count($symptom1); $i++){
// 		$ssymptom = handlequote($symptom1[$i]);
// 		$sql = 'select * from disease2symptom where symptom = "' . $ssymptom . '"';
// 		$result = QuerySQL("relationship", $sql);
// 		for($j = 0; $row = mysql_fetch_array($result); $j++, $k++){
// 			$doid2name[$k] = $row['disease'];
// 		}
// 	}

// 	/*根据doid1得出的symptom，再搜索所有关联doid2，其中重复的doid2数就是具有相同病症的doid2数*/	
// 	$num = array();
// 	$num = CountDuplicate($doid2name);
// 	if(arsort($num) == false)	
// 		exit("sort error!!<br/>");
// 	// showArray("num", $num);
// 	//show
// 	foreach ($num as $dn => $value) {
// 		$id = Name2Id($dn, "doid", "test");
// 		if(count($symptom1) == $value){}
// 		elseif($value > 2)
// 			echo('<p><a href="javascript:LayerPage(\''. $id . '\');">' . $id . ' ' . $dn . ' 相关病症个数：' . $value . '</a></p>');
// 	}





/*
得出doid1, doid2, 之后动态动态匹配相同的疾病个数
速度太慢！（10+秒）淘汰

	//doid2去重
	$doid2name = DupilicaRemove($doid2name);
	// showArray("doid2name", $doid2name);
	//doid2->disease2symptom->symptom2(多对多)
	$num = array();
	foreach ($doid2name as $key => $value) {
		# code...
		$sql = 'select * from disease2symptom where disease = "' . $value . '"';
		$result = QuerySQL("relationship", $sql);
		$symptom2 = array();
		while($row = mysql_fetch_array($result)){
			array_push($symptom2, $row['symptom']);
		}
		//symptom2 vs. symptom1
		//count(symptom2 in symptom1) -> num
		$num[$value] = Match($symptom1, $symptom2);
	}	
	//sort
	if(arsort($num) == false)	
		exit("sort error!!<br/>");
	// showArray("num", $num);
	//show
	foreach ($num as $name => $value) {
		$id = Name2Id($name, "doid", "test");
		if($value > 2)
			echo('<p><a href="javascript:LayerPage(\''. $id . '\');">' . $id . ' ' . $name . '</a></p>');
	}
*/

?>