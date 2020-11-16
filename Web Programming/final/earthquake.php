<?php
header("Access-Control-Allow-Origin: *");
$aq = $_POST["aq"];
$context  = stream_context_create(array('http' => array('header' => 'Accept: application/json')));
$url ='earthquake.json';
$data = file_get_contents($url, false, $context);
$data = json_decode($data);
//print_r($data);
//print_r($aq);
$a=0;
print ("<table><tr style='background-color:#F0C01F'><td>日期</td><td>時間</td><td>芮氏規模</td><td>深度</td><td>震央</td><td>縣市</td><td>地點</td></tr>");
foreach ($data as $key)
{
    //$station = $key->{"scope"};
    //$value = $key->{"identifier"};
	$cpy = $key->{"dataset"};
	$cpy2 = $cpy->{"catalog"};
	$cpy3 = $cpy2->{"earthquakeinfo"};

	foreach ($cpy3 as $point){
		$time = $point->{"originTime"};
		$loc = $point->{"location"};
		$loca = $point->{"locate"};
		$t = $point->{"time"};
		
		$magnitude = $point->{"magnitude"};
		$magnitudeValue = $magnitude->{"magnitudeValue"};
		
		$depth = $point->{"depth"};
		$text = $depth->{"#text"};

		//echo $a%2;
		$epicenter = $point->{"epicenter"};
		$epicenterLon = $epicenter->{"epicenterLon"};
		$text2 = $epicenterLon->{"#text"};
		$epicenterLat = $epicenter->{"epicenterLat"};
		$text3 = $epicenterLat->{"#text"};
		if($aq === $loc){
			if($a%2===0){
				print ("<tr style='background-color:white'><td>$time</td><td>$t</td><td>$magnitudeValue</td><td>$text</td><td>$text2 $text3</td><td>$loc</td><td>$loca</td></tr>");
			}else{
				print ("<tr style='background-color:#61EE8A'><td>$time</td><td>$t</td><td>$magnitudeValue</td><td>$text</td><td>$text2 $text3</td><td>$loc</td><td>$loca</td></tr>");
			}
			
			$a+=1;
		}
		if($aq === "0"){
			if($a%2===0){
				print ("<tr style='background-color:white'><td>$time</td><td>$t</td><td>$magnitudeValue</td><td>$text</td><td>$text2 $text3</td><td>$loc</td><td>$loca</td></tr>");
			}else{
				print ("<tr style='background-color:#61EE8A'><td>$time</td><td>$t</td><td>$magnitudeValue</td><td>$text</td><td>$text2 $text3</td><td>$loc</td><td>$loca</td></tr>");
			}
			
			$a+=1;
		}
	}

}
print ("</table>");
?>