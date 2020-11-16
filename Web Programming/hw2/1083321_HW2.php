<?php

require_once('TCPDF/tcpdf_import.php');

/*---------------- Sent Mail Start -----------------*/
	function mail_attachment ($from , $to, $subject, $message, $attachment){
         $fileatt = $attachment; // Path to the file
         $fileatt_type = "application/octet-stream"; // File Type 
         
                  
         $email_from = $from; // Who the email is from
       
         $email_subject =  $subject; // The Subject of the email 
         $email_txt = $message; // Message that the email has in it 
         $email_to = $to; // Who the email is to
         
         $headers = "From: ".$email_from;
         $file = fopen($fileatt,'rb'); 
         $data = fread($file,filesize($fileatt)); 
         fclose($file); 
         
         //$msg_txt="\n\n You have recieved a new attachment message from $from";
         $semi_rand = md5(time()); 
         $mime_boundary = "==Multipart_Boundary_x{$semi_rand}x"; 
         $headers .= "\nMIME-Version: 1.0\n" . "Content-Type: multipart/mixed;\n" . " boundary=\"{$mime_boundary}\"";
         
         //$email_txt .= $msg_txt;
			
         $email_message = "This is a multi-part message in MIME format.\n\n" . "--{$mime_boundary}\n" . "Content-Type:text/html; 
            charset = \"iso-8859-1\"\n" . "Content-Transfer-Encoding: 7bit\n\n" . 
            $email_txt . "\n\n";
				
         $data = chunk_split(base64_encode($data));
         
         $email_message .= "--{$mime_boundary}\n" . "Content-Type: {$fileatt_type};\n" .
            " name = \"{$fileatt}\"\n" . //"Content-Disposition: attachment;\n" . 
             "Content-Transfer-Encoding: base64\n\n" . $data . "\n\n" . "--{$mime_boundary}--\n";
				
         mail($email_to, $email_subject, $email_message, $headers);
         
    } 


include("phpqrcode/qrlib.php");
/*include('config.php');*/
$name = $_POST["name"];
$gender = $_POST["gender"];
$num = $_POST["num"];
$self = $_POST["self"];
$tel = $_POST["tel"];
$meal = $_POST["meal"];

$to = $_POST["email"];
$subject = "2019四資迎新-監獄風雲報名通知";
$message = "您已成功報名2019四資迎新-監獄風雲<br><br>以下是您的報名資料:<br>姓名 : $name<br>性別 : $gender<br>學號 : $num<br>身分證字號 : $self<br>手機號碼 : $tel<br>飲食習慣 : $meal<br><br>";
$headers = "From: pinghe.yeh@gmail.com";

/*$codeContents = 'mailto:'.$to.'?subject='.urlencode($subject).'&message='.urlencode($message);
QRcode::png($codeContents, 'yy.png', QR_ECLEVEL_L, 3);*/

$URL='http://'.$_SERVER['HTTP_HOST'].'/information.pdf';
QRcode::png($URL, 'xx.png');
//$message .= "http://192.168.43.42:8080/xx.png";

//echo $message;
//mail("$to","$subject","$message","$headers");
mail_attachment($headers, $to, $subject, $message, "xx.png");
/*---------------- Sent Mail End -------------------*/

/*---------------- Print PDF Start -----------------*/
$pdf = new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);
$pdf->setPrintHeader(false);
$pdf->setPrintFooter(false);
$pdf->SetFont('stsongstdlight','', 20);
/*$pdf->SetFont('cid0jp','', 18); */
$pdf->AddPage();

$name = $_POST["name"];
$gender = $_POST["gender"];
$num = $_POST["num"];
$self = $_POST["self"];
$email = $_POST["email"];
$tel = $_POST["tel"];
$meal = $_POST["meal"];

$html = <<<EOF
	<head>
		<link rel = "stylesheet" type = "text/css"
				href = "blue.css">
	</head>
	<body>
		<h1 align="center">2019四資迎新-監獄風雲</h1>
		<p><strong>活動宗旨 : </strong>讓新生認識元智大學校園，提前適應大學生活</p>
		<p><strong>主辦單位 : </strong>元智大學資工、資管、資英、資傳系學會</p>
		<p><strong>活動對象 : </strong>資工、資管、資英、資傳系的新生</p>
		<p><strong>活動日期 : </strong><em style="color:red">2019/8/29 - 2019/8/23</em></p>
		<p><strong>活動地點 : </strong><em style="color:red">元智大學全區</em></p>
		<p><strong>住宿地點 : </strong><em style="color:red">元智大學男女1宿</em></p>
		<p><strong>報名費用 : </strong><em style="color:red">4000元 ~ 6/30以前報名享早鳥優惠3700元</em></p>
		<p><strong>聯絡方式 : 總召:王小明 0900-000-000 副召:王大明 0900-000-001</strong></p>
					
		<table border = "1">
			<tr>
				<td align="center" colspan="3" rowspan="1"><strong>報名資料</strong></td>
			</tr>
			<tr>
				<td align="center">name : <em>$name</em></td>
				<td align="center" colspan="2">I.D. number : <em>$self</em></td>
			</tr>
			<tr>
				<td align="center">gender : <em>$gender</em></td>
				<td align="center" colspan="2">phone number : <em>$tel</em></td>
			</tr>
			<tr>
				<td align="center">student id : <em>$num</em></td>
				<td align="center" colspan="2">meal : <em>$meal</em></td>
			</tr>
			<tr>
				<td align="center" colspan="3">E-mail : <em>$email</em></td>
			</tr>
		</table>
	</body>
EOF;
/*---------------- Print PDF End -------------------*/

$pdf->writeHTML($html);
$pdf->lastPage();
$pdf->Output('information.pdf', 'I');
$pdf->Output('C:\xampp\htdocs\information.pdf', 'F');
