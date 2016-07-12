#!/usr/bin/python
import httplib
import hashlib
import json

'''
json data
{
    "ver": "TVOS.04.15.010.03.17",
    "url": "http://172.21.29.243/aosp_mangosteen-ota-TVOS.04.15.010.03.17.zip",
    "size": "395984367",
    "md5": "28b4d7f751a1b0a9f3a7e7cf78734c19"
}
'''

def main():
  conn = httplib.HTTPConnection("172.21.29.243", 80)
  conn.request("GET", "/test.php?version=TVOS.04.15.010.03.17")
  response = conn.getresponse()
  if response.status != httplib.OK:
    print response.status, response.reason
  data = response.read()
  print data
  #print data
  #conn.close()
  json_data = json.JSONDecoder().decode(data)
  print json_data
  package_download_url = json_data["url"]
  #package_name = package_download_url[package_download_url.strrchr('/'),]
  package_name = package_download_url[package_download_url.rfind("/")+1:]
  print package_name
  md5_value = json_data["md5"]
  file_size = json_data["size"]
  conn.request("GET", package_download_url)
  #conn.request("GET", "/aosp_mangosteen-ota-TVOS.04.15.010.03.17.zip")
  response_down = conn.getresponse()
  if response.status != httplib.OK:
    print response_down.status, response_down.reason
  data_down = response_down.read()
  md5_cal_value = hashlib.md5(data_down).hexdigest()
  if md5_value == md5_cal_value:
    print "OTA upgrade pacakge download finished\n"
    output_file = open(package_name, "w")
    output_file.write(data_down)
    output_file.close()
  conn.close()

if __name__ == '__main__':
  main()