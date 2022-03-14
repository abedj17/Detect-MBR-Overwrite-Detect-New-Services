import os
index=0
my_file1 = open("A2.txt", "r")
content1 = my_file1.read()
#print(content1)

content_list1 = content1.split("\n")
my_file1.close()
os.system("powershell  Get-Service -Name * ^| Format-Table -Property Name -auto > new_serv.txt")
my_file2 = open("new_serv.txt", "r")
content2 = my_file2.read()
content_list2 = content2.split("\n")
my_file2.close()
#print(content2)
'''

#if content1 == content2:

for a in content_list2:
    for b in content_list1:
        if a==b:
            index=1
        if index==1:
            index=0
            break
    if index==1:
        print(a)
'''

diff_list=[]
for a in content_list2:
    if a not in content_list1:
        diff_list.append(a)
if diff_list==[]:
    print("Same Services")
else:
    print(diff_list)
