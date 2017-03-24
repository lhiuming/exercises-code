# My Notes about attacklab

Todos:

- task 2;
- task 3;
- task 4;
- task 5;

## Task 1 (level 1 of ctarget)

Since inputs are read into the stack from low address to high address,
writing the <touch_1> address at the end of the input sequence would overwrite
the top side of the buffer.

Buffer size is 40 (bytes), so just plug the <touch_1> address at the 41 ~ 48
positions of the input stream. This would overwrite the return address of
<getbuf>, which is located right at the top of the pre-allocated buffer.
