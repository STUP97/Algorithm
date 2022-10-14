import re

#6개의 면을 1번 자리로 두고 위 아랫면 서로 비교. 일치하면 회전하며 비교.
def Cube_match(cube_1, cube_2):
  for i in range (6):
    if i < 4:
      temp = cube_1[0] 
      cube_1[0] = cube_1[4]
      cube_1[4] = cube_1[5]
      cube_1[5] = cube_1[1]
      cube_1[1] = temp
    elif i == 4:
      temp = cube_1[0] 
      cube_1[0] = cube_1[3]
      cube_1[3] = cube_1[5]
      cube_1[5] = cube_1[2]
      cube_1[2] = temp
    else :
      temp = cube_1[0] 
      cube_1[0] = cube_1[4]
      cube_1[4] = cube_1[5]
      cube_1[5] = cube_1[1]
      cube_1[1] = temp
      temp = cube_1[0] 
      cube_1[0] = cube_1[4]
      cube_1[4] = cube_1[5]
      cube_1[5] = cube_1[1]
      cube_1[1] = temp
    if cube_1[0] == cube_2[0] and cube_1[5] == cube_2[5]:
      for j in range (4):
        temp = cube_1[1]
        cube_1[1] = cube_1[2]
        cube_1[2] = cube_1[4]
        cube_1[4] = cube_1[3]
        cube_1[3] = temp
        if cube_1[1:5] == cube_2[1:5]:
          return True
  return False


#파일 입출력
input_fp = open("cube.inp", 'r')
output_fp = open("cube.out", 'w')  
    
#반복 시작
while True:
  str_cube_data = input_fp.readline()
  #받아온 데이터 문자열 -> 문자 리스트로 묶어내기.   ... import re
  cube_data = re.findall("\w", str_cube_data)
  cube_1 = cube_data[0:6]
  cube_2 = cube_data[6:12]
  R_cnt = cube_data.count('r')
  B_cnt = cube_data.count('b')
  G_cnt = cube_data.count('g')
  stop_signal = max(R_cnt,B_cnt,G_cnt)
  IsMatch = Cube_match(cube_1,cube_2)
  if IsMatch:
    output_fp.write("TRUE\n")
  else:
    output_fp.write("FALSE\n")
  if stop_signal == 12:
    break
  

input_fp.close()
output_fp.close()
