# 设计文档

## 概述

​		本项目的类图如下：

![image-20240604105332573](.\img\image-20240604105332573.png)

​		下面是对于每个类的详细说明。

## `jsonexplorer.hpp`

### `JsonExplorer` 类

- **功能**: 解析 JSON 文件并展示为树形结构。

- 成员变量:

  私有成员:

  - `AbstractIconFactory icon_factory`: 图标工厂，用于生成不同类型的图标。
  - `AbstractStyleFactory style_factory`: 样式工厂，用于生成不同类型的样式。
  - `int max_len`: 用于记录最大长度，以便在绘制时对齐。
  - `std::shared_ptr<Component> root`: JSON 的根组件节点。

- 方法:

  - `JsonExplorer(int style_id, int icon_id)`: 构造函数，初始化图标工厂和样式工厂的 ID。
  - `_load(std::string filename)`: 从文件加载 JSON，预处理并解析为组件树。
  - `show()`: 显示 JSON 组件树。
  - `parse_json(const json& j, const std::string& key, int level)`: 递归解析 JSON 对象和数组，生成对应的组件树。

​		这里使用了建造者方法，`jsonexplorer`只需使用`abstract_factory.hpp`中的工厂方法来建造`Icon`类和`Style`类，而无需关心细节，便于以同样的方式使用不同的`Icon`和`Style`。



## `abstract_factory.hpp` 

### `AbstractIconFactory` 类

- **功能**: 用于创建 `Icon` 对象的工厂类，根据设定的 ID 生成不同类型的 `Icon` 对象。

- 方法:

  - `create()`: 根据 `id` 创建并返回一个 `Icon` 对象的共享指针。
- `set_id(int)`: 设置工厂生成的 `Icon` 类型的 ID。

### `AbstractStyleFactory` 类

- **功能**: 用于创建 `Style` 对象的工厂类，根据设定的 ID 和传入的 `Icon` 对象生成不同类型的 `Style` 对象。

- 方法:

  - `create(std::shared_ptr<Icon>)`: 根据 `id` 和传入的 `Icon` 对象创建并返回一个 `Style` 对象的共享指针。
- `set_id(int)`: 设置工厂生成的 `Style` 类型的 ID。

​		上述两个类使用了抽象工厂的设计模式，旨在使`JsonExplorer`以相同的方式构造`Icon`和`Style`的继承类，使得只需修改抽象工厂，以及添加新的继承类，即可完成图标族和风格的添加。



## `Component.hpp`

### `Component` 类

- **功能**: 抽象基类，表示树结构中的节点（包括容器节点和叶子节点）。
- 成员变量:
  - `title`: 属性的名称。
  - `level`: 节点的深度。
- 方法:
  - `draw(Style&, std::string, int, int)`: 虚函数，用于绘制节点。
  - `add(std::shared_ptr<Component>)`: 虚函数，用于添加子节点。

### `Container` 类

- **功能**: 继承自 `Component` 类，表示树结构中的容器节点，可以包含子节点。
- 成员变量:
  - `childs`: 子节点的集合。
- 方法:
  - `draw(Style&, std::string, int, int)`: 使用指定的样式绘制容器节点及其子节点，计算并传递前缀。
  - `add(std::shared_ptr<Component>)`: 向子节点集合中添加子节点。

### `Leaf` 类

- **功能**: 继承自 `Component` 类，表示树结构中的叶子节点，包含具体的属性值。
- 成员变量:
  - `value`: 叶子节点的值。
- 方法:
  - `draw(Style&, std::string, int, int)`: 使用指定的样式绘制叶子节点。

​		上述基类以及继承类使用了组合模式，为了能基于Component形成一个关于json的树状结构，并能将其容纳在同一容器里，便于管理。



## `style_family.hpp`

### `Style` 类

- **功能**: 抽象基类，定义绘制容器节点和叶子节点的接口。使用 `Icon` 对象来表示节点的图标。
- 方法:
  - `set_icon(const Icon&)`: 设置 `Icon` 对象。
  - `draw_container(const std::string&, std::string&, int, int)`: 虚函数，用于绘制容器节点，返回下一个前缀。
  - `draw_leaf(const std::string&, const std::string&, std::string&, int, int)`: 虚函数，用于绘制叶子节点。

### `StyleTree` 类

- **功能**: 继承自 `Style` 类，使用树结构样式绘制容器节点和叶子节点。
- 方法:
  - `draw_container(const std::string&, std::string&, int, int)`: 绘制树结构中的容器节点，返回下一个前缀。
  - `draw_leaf(const std::string&, const std::string&, std::string&, int, int)`: 绘制树结构中的叶子节点。

### `StyleRectangle` 类

- **功能**: 继承自 `Style` 类，使用矩形框样式绘制容器节点和叶子节点。
- 方法:
  - `draw_container(const std::string&, std::string&, int, int)`: 绘制矩形框中的容器节点，返回下一个前缀。
  - `draw_leaf(const std::string&, const std::string&, std::string&, int, int)`: 绘制矩形框中的叶子节点。

### 辅助函数

- **`repeat(int times, std::string str)`**: 将指定字符串重复给定次数，返回重复后的字符串。



## `icon_family.hpp`

### `Icon` 类

- **功能**: 管理表示容器节点和叶子节点的图标。提供获取这些图标的接口和浅拷贝赋值运算符。
- 方法:
  - `get_container_icon()`: 返回表示容器节点的图标。
  - `get_leaf_icon()`: 返回表示叶子节点的图标。
  - `operator=`: 实现浅拷贝赋值。

### `Icon1` 类

- **功能**: 继承自 `Icon` 类，使用特定字符初始化父类构造器。
- **构造器**: `Icon1()`: 使用特殊字符 `"♢"`（空心菱形）和 `"♧"`（空心梅花）初始化。

### `Icon2` 类

- **功能**: 继承自 `Icon` 类，使用特定字符初始化父类构造器。
- **构造器**: `Icon2()`: 使用特殊字符 `"♦"`（实心菱形）和 `"♣"`（实心梅花）初始化。
