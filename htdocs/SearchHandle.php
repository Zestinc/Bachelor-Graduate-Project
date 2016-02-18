<?php 
require_once("./RelaGO.php");
//Connect to database & select the db
$con = mysql_connect("localhost:8889","root","root");
if ($con == 0)
	exit("mysql_connect error");
//Get the data from web and process.
$id = htmlspecialchars($_REQUEST["q"]);	//id的具体意义参看各函数的参数
$sql = $id;
$sum = 0;		//区分id检索模式和name模糊检索模式 当sum==0, 表示名字搜索失败，启动id搜索
$ans = "";		
nameMatch($sql, "envo", $con, "环境");
nameMatch($sql, "doid", $con, "疾病");
Symptom2Doid($sql, $con);
// AddResult("##");
nameMatch($sql, "go", $con, "基因");
Symptom2Go($sql, $con);
// AddResult("##");

if($sum == 0)
{
	$ans = "";
	idMatch($sql, "envo", $con);
	idMatch($sql, "doid", $con);
	idMatch($sql, "go", $con);
}
echo($ans);

function Symptom2Doid($symptom, $con){
	$sql = 'select * from disease2symptom where symptom like "' . '%' . $symptom . '%"';
	$result = QuerySQL("relationship", $sql);
	while($row = mysql_fetch_array($result)){
		$name = $row['disease'];
		$id = Name2Id($name, "doid", "test");
		AddResult('@@' . $id . ' ' . $name);
		$GLOBALS['sum'] = $GLOBALS['sum'] + mysql_num_rows($result);	
	}
	AddResult("##");
	// echo($GLOBALS['ans']);
}

function Symptom2Go($symptom, $con){
	//symptom -> disease2symptom -> disease(一对多)
	$sql = 'select * from disease2symptom where symptom = "%' . $symptom . '%"';
	$result = QuerySQL("relationship", $sql);
	$disease = "";
	$result1 = "";
	$row1 = "";
	while($row = mysql_fetch_array($result)){
		$disease = $row['disease'];
		//disease -> disease2gene -> go_id（多对多）
		$sql = 'select * from disease2gene where disease = "' . $disease . '"';
		$result1 = QuerySQL("relationship", $sql);
		$go_id = "";
		$go_name = "";
		while($row1 = mysql_fetch_array($result1)){
			$go_id = $row1['go_id'];
			//go_id -> name
			$go_name = Id2Name("go", $go_id, "go");
			//AddResult	'@@'为分割符，用于前台处理
			AddResult('@@' . $go_id . $go_name);
			$GLOBALS['sum'] = $GLOBALS['sum'] + mysql_num_rows($result1);
		}
	}
	AddResult("##");
}

//将要输出的数据打包
function AddResult($st)
{
	$GLOBALS['ans'] = $GLOBALS['ans'] . $st;
}

//根据名字匹配相关节点
function nameMatch($name, $db, $con, $root){
	$db_mysql = "";
	if($db == "doid")
		$db_mysql = "test";
	else 
		$db_mysql = $db;
	// if(mysql_select_db($db_mysql, $con) == false)
		// exit("mysql_select_db error" . " name:" . $name . " db:" . $db);
	$sql = "select * from " . $db . " where name like \"" . "%" . $name . "%" . '"';
	// $result = mysql_query($sql, $con);
	$result = QuerySQL($db_mysql, $sql);
	if($result == false) 
		exit("ERROR WHILE PROCESSING nameMatch FUNCTION!!!" . $sql);
	$GLOBALS['sum'] = $GLOBALS['sum'] + mysql_num_rows($result);
	AddResult($root);
	while($row = mysql_fetch_array($result))
	{	
		AddResult('@@' . $row[$db . "_id"] . " " . $row['name']);
	}
	if($db == "envo")
		AddResult("##");
}

function idMatch($id, $db, $con){
	$db_mysql = "";
	if($db == "doid")
		$db_mysql = "test";
	else 
		$db_mysql = $db;
	if(mysql_select_db($db_mysql, $con) == false)
		exit("mysql_select_db error" . " id:" . $id . " db_mysql:" . $db_mysql);	
	$sql = "select * from " . $db . " where " . $db . "_id = \"" . $id . '"';
	$result = mysql_query($sql, $con);
	if($result == false) 
		exit("ERROR WHILE PROCESSING nameMatch FUNCTION!!!". $sql);
	AddResult($db);
	while($row = mysql_fetch_array($result))
	{	
		AddResult('@@' . $row[$db . '_id'] . " " . $row['name']);
	}
	AddResult("##");
}

mysql_close($con);
?>