<?php
$version = $_REQUEST['version'];
$device = $_REQUEST['device'];
/*
json data
{
    "ver": "TVOS.04.15.010.03.17",
    "url": "http://172.21.29.243/aosp_mangosteen-ota-TVOS.04.15.010.03.17.zip",
    "size": "395984367",
    "md5": "28b4d7f751a1b0a9f3a7e7cf78734c19"
}
*/
if ($device == "miraclefruit")
{
    if ($version == "TVOS.04.15.010.03.08")
    {
        $otapackage = "aosp_miraclefruit-ota-TVOS.04.15.010.03.09.zip";
        $ver = "TVOS.04.15.010.03.09";
        $url = "http://172.21.29.243/aosp_miraclefruit-ota-TVOS.04.15.010.03.09.zip";
        $size = 400624907;
        $md5 = "aea23a806389fb03db575d0b4da2af4e";
        $json_data = Array('ver'=>$ver, "url"=>$url, 'size'=>$size, 'md5'=>$md5);
        echo json_encode($json_data);
    }
    else
    {
        echo "no OTA upgrade package for the version : ".$version."\n";
    }
}
else
{
    echo "no OTA upgrade package for the version : ".$version."\n";
}
?>