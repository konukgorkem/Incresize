### Incresize

# What is it?
Basically it increases the size of your .exe file according to size you want.

# But why?
Because the aim is making the exe file not uploadable for virustotal.com, so target can't upload and anlyze the payload. Eventually antiviruses can't detect your payload. Currently Virustotal supports 650 MB of files. Don't worry, even if they support more of that in the future, Incresize will still help you.

# How does it works?
It appends unnecessary data to exe so the exe size get bigger. You can choose different modes. Which are:

1. Lorem ipsum mode: it creates lorem ipsum and appends to the .exe.
2. Binary mode: it creates 0 and 1, and it appends to the .exe.
3. Custom mode: you can choose the text you want to add to the .exe.

After choosing a mode, it will ask you to choose:
1. Byte mode
2. Megabyte mode
3. Gigabyte mode

Which are basically will determine the size of the txt file to be created (which will be dummy.txt) then it will append it to your selected .exe file.
(Lets say you chose Megabyte mode (Press 1) and then you want to create 5 MB of file, you will write 5.)

Then it will ask you your .exe file or your payload name you have. Then it will ask you to enter name for output .exe. After you input, it will create your combined .exe file which is your orginal exe with bigger size. 

It may take longer to create the txt file according to your computer's specs and the size you want to create.

# Screenshot
![](https://github.com/konukgorkem/Incresize/blob/main/img/incresize.png)


