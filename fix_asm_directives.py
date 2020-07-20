# Read in the file
with open('out\out.s', 'r') as file :
  filedata = file.read()

# Replace the target string
filedata = filedata.replace('.byte', 'dc.b')
filedata = filedata.replace('.word', 'dc.w')
filedata = filedata.replace('.long', 'dc.l')
filedata = filedata.replace('.def', ';.def')
filedata = filedata.replace('.globl', ';.globl')
filedata = filedata.replace('.data', ';.data')
filedata = filedata.replace('.opt', ';.opt')
filedata = filedata.replace('.align', ';.align')
filedata = filedata.replace('.file', ';.file')
filedata = filedata.replace('.text', ';.text')
filedata = filedata.replace('.comm', ';.comm')
filedata = filedata.replace('.lcomm', ';.lcomm')

# Write the file out again
with open('out\out.s', 'w') as file:
  file.write(filedata)
  