# FlowTransformer
Cross-Platform Flow Transformer Qt/C++. 
Transforms inputs (XML) following a structure X into outputs (XML) following a structure Y using a set of mappings. 
You could create your own mapping using the GUI.

Used Expat lib to extract from XML files the structures.
Structures are shown to the user and can modify them manually, create mapping between them using a drag and drop from source to target.
There is also a table which summarises all mapping.

These mappings are serialized for future use.
In the second tab, magic happens. You upload your input and a mapping.

It will use target model, the mapping and data in source files to create the output.
(A verification layer will added in upcomming release)

This is a preview, still under tests.
For testers, you can build your own solution or use builds on Win32 and OSX.
And of course, if you have comments or suggestions. I'll be more than happy to hear them.

Build :
https://www.dropbox.com/sh/ndoxot0y4ecpsuh/AAAPAz6BtVTpeSzIFExp_xiha?dl=0
