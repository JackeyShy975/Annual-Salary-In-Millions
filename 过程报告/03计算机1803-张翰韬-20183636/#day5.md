# day5

  今天虽然没有安排编译原理实验课，还是在上午上完数字电路后，抽了一下午的时间继续推进了工作。主要推进了两方面的工作。

## 1.语义分析

  继续昨天插的语义动作，继续在语法分析的基础上插了一些语义动作。主要集中在算数表达式和一些变量的生成处。

1.加了个产生临时变量的函数，用来处理t1,t2这种临时变量的生成。

2.改变了一些语法分析函数，通过一些传值的方式使得能够正确的填写符号表。

3.完成了声明语句，赋值语句，算数表达式的大部分工作，卡在了void *和vector迭代器不兼容的地方，正在努力尝试修复。感觉在用c++建立符号表系统和维护符号表系统时，各种指针域很容易弄混，也很容易乱指。所以打算在语义分析处多耗点时间，将符号表系统建立好，维护好。这样在后期处理其他部分的时候，使用起来就更方便了。

4.注意到了类型转换的问题。因为当时从词法分析处传过来的时候只保留了类型码和token的值，因此只能判断一个token值中存的是常量。但具体是int形式的还是double等形式的确定不了。因此类型的识别还需要再语义分析处继续完善。只有在语义分析处完善了类型的识别，才能保证根据文法推导出正确的动作。同时由于符号表在设计常量表的时候，根据不同的常量分别设置了不同的常量表。因此只有准确确定出来常量的类型，才能在填写常量表和建立总符号表和常量表之间的联系（主要是addr处）不会出错。

## 2.继续修改了一些符号表的设计

  1.在符号表里加了一些迭代器的索引。使得符号表中addr部分可以精确的访问到一些常值，数组等。将作用域栈由stack改为了vector的结构，主要是为了遍历前面压进去的作用域。因为c++STL结构中STACK无法遍历，只有改为vector才能遍历，同时通过引入有关vector的iterator可以准确的定位到存储数据的地方，便于及时的读取和删除。

  2.完善了类型表的地方，类型表的一些类型等还未齐全，补充了一下相应的类型。