<?php
require_once("./RelaGO.php");
/**********************
***********************
*******其他函数*********
***********************
**********************/
function arrFind($arr, $content)
{
	while(key($arr) != $content)	
		next($arr);
	return current($arr);
}

/**********************
***********************
*******分类型输出*******
***********************
**********************/
function echost($pre, $post)
{
	if(is_array($post)){
		for($i=0; $i<count($post); $i++){
			if($post[$i] == "") return; 
			echo $pre . $post[$i] . "<br/>";
		}
	}
	else 
	{
		if($post == "") return; 
		echo $pre . $post . "<br/>";
	}
}

function echobool($pre, $post)
{
	echo $pre;
	if($post) 
		echo "true";
	else 
		echo "false";
	echo "<br/>";
}

/**********************
***********************
*******查询表内容********
***********************
**********************/
function mySearch($table, $content, $condition, $db)
{
	$sql = "SELECT * FROM " . $table . " where ". $condition;
	$result = mysql_query($sql, $db);
	if($result == false)
		exit("error at mySearch\n   error sql: " . $sql);
	$rtValue = array();
	while($row = mysql_fetch_array($result))
	{
		// while(key($row) != $content)	
		// 	next($row);
		$temp = $row[$content];
		array_push($rtValue, $temp);
	}
	return $rtValue;
}


/**********************
***********************
*******数据处理********
***********************
**********************/

function doid($con, $doid_id)	//sql为搜索框中输入的内容
{
	$sql = "SELECT * FROM doid where doid_id = \"" .  $doid_id . "\"";
	$result = mysql_query($sql, $con);
	if($result == false) 
		exit("ERROR while processing doid function!");

	while($row = mysql_fetch_array($result))//对查询得到的每一条
	{
		echo "[Term]" . "<br/>"; 	
		echost("", $doid_id);
		echost("name: ",$row['name']);
		echost("created_by: ", $row['created_by']);
		echost("creation_date: ", $row['creation_date']);
		echost("comment: ", $row['comment']);
		echobool("is_obsolete: ", $row['is_obsolete']);
	}

	//下面是 一对多 or 多对多 的表的输出处理
	$condition = "doid_id = \"" . $doid_id . '"';

	$res = mySearch("xref", "xref", $condition, $con);
	echost("xref: ", $res);

	$res = mySearch("alt_id", "alt_id", $condition, $con);
	echost("alt_id: ", $res);

	$res = mySearch("def", "def", $condition, $con);
	echost("def: ", $res);

	$res = mySearch("synonym", "synonym", $condition, $con);
	echost("synonym: ", $res);

	$res = mySearch("subset", "subset", $condition, $con);
	echost("subset: ", $res);


}

function go($con, $go_id)
{
	$sql = "SELECT * FROM go where go_id = \"" .  $go_id . "\"";
	$result = mysql_query($sql, $con);
	if($result == false) 
		exit("ERROR WHILE PROCESSING go FUNCTION!!!");

	while($row = mysql_fetch_array($result))
	{
		echost("", $row['go_id']);
		echost("name: ", $row['name']);
		echost("namespace: ", $row['namespace']);
		echost("comment: ", $row['comment']);
		echobool("is_obsolete: ", $row['is_obsolete']);
	}
	//下面是 一对多 or 多对多 的表的输出处理
	$condition = "go_id = \"" . $go_id . '"';
	$res = mySearch("alt_id", "alt_id", $condition, $con);
	echost("alt_id: ", $res);

	$res = mySearch("broad_synonym", "broad_synonym", $condition, $con);
	echost("broad_synonym: ", $res);

	$res = mySearch("consider", "consider", $condition, $con);
	echost("consider: ", $res);

	$res = mySearch("def", "def", $condition, $con);
	echost("def: ", $res);

	$res = mySearch("exact_synonym", "exact_synonym", $condition, $con);
	echost("exact_synonym: ", $res);

	$res = mySearch("narrow_synonym", "narrow_synonym", $condition, $con);
	echost("narrow_synonym: ", $res);

	$res = mySearch("related_synonym", "related_synonym", $condition, $con);
	echost("related_synonym: ", $res);

	$res = mySearch("replaced_by", "replaced_by", $condition, $con);
	echost("replaced_by: ", $res);

	$res = mySearch("subset", "subset", $condition, $con);
	echost("subset: ", $res);

	$res = mySearch("xref", "xref", $condition, $con);
	echost("xref: ", $res);
	//特殊表处理
	//Relationship
}

function envo($con, $envo_id)
{
	$sql = "SELECT * FROM envo where envo_id = \"" .  $envo_id . "\"";
	$result = mysql_query($sql, $con);
	if($result == false) 
		exit("ERROR WHILE PROCESSING envo FUNCTION!!!");

	while($row = mysql_fetch_array($result))
	{
		echost("", $row['envo_id']);
		echost("name: ", $row['name']);
		echost("namespace: ", $row['namespace']);
		echost("comment: ", $row['comment']);
		echost("created_by: ", $row['created_by']);
		echost("creation_date: ", $row['creation_date']);
		echost("expand_assertion_to: ", $row['expand_assertion_to']);
		echobool("is_class_level: ", $row['is_class_level']);
		echobool("is_metadata_tag: ", $row['is_metadata_tag']);
		echobool("is_obsolete: ", $row['is_obsolete']);
		echobool("is_symmetric: ", $row['is_symmetric']);
		echobool("is_transitive: ", $row['is_transitive']);
		echost("property_value: ", $row['property_value']);
		echost("replaced_by: ", $row['replaced_by']);
	}
	//一对多 or 多对多 的表的输出处理
	$condition = "envo_id = \"" . $envo_id . '"';
	$res = mySearch("alt_id", "alt_id", $condition, $con);
	echost("alt_id: ", $res);

	$res = mySearch("consider", "consider", $condition, $con);
	echost("consider: ", $res);

	$res = mySearch("def", "def", $condition, $con);
	echost("def: ", $res);

	$res = mySearch("subset", "subset", $condition, $con);
	echost("subset: ", $res);

	$res = mySearch("synonym", "synonym", $condition, $con);
	echost("synonym: ", $res);

	$res = mySearch("xref", "xref", $condition, $con);
	echost("xref: ", $res);
	//特殊表处理
	//disjoint_from
	//intersection_of
	//relationship

}

//Start
$con = mysql_connect('localhost:8888','root','root');
if (!$con)
{
	die('Could not connect: ' . mysql_error());
}
$sql = htmlspecialchars($_REQUEST["q"]);
$fir = substr($sql, 0, 1);
if($fir == "E" || $fir == "C" || $fir == "P")
{
	mysql_select_db("envo", $con);
	envo($con, $sql);
	RelaGO($con, $sql, "envo");
}
elseif($fir == "G")
{
	mysql_select_db("go", $con);
	go($con, $sql);
	RelaGO($con, $sql, "go");
}
elseif($fir == "D")
{
	mysql_select_db("test", $con);
	doid($con, $sql);
	RelaGO($con, $sql, "doid");
	Doid2Doid($con, $sql);
}
elseif ($fir == "^") {	//从主页跳进搜索页面时候的显示信息
	exit("<h1>This is the Graduation Design Project</h1>
	<p>Copyright belongs to zestinc and 王也</p>
	<p>Designed by Qing</p>");
}
elseif ($fir == "@"){	//对于尚未收录的节点的显示信息
	exit("<h1>该节点信息未收录，无法显示详细信息</h1>");
}
else 
	exit("<h1>从左边列表中点击想要查看的节点</h1>");
mysql_close($con);
?>