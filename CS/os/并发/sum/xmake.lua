-- 设置项目名称
set_project("race_condition_demo")

-- >>>>> 修改这里，明确指定使用 gcc 工具链 <<<<<
-- xmake 会尝试找到系统上安装的 MinGW-GCC
set_toolchains("gcc")

-- 添加一个可执行目标
target("race_condition")
    -- 设置目标类型为可执行文件
    set_kind("binary")

    -- 添加源文件
    add_files("main.c")

    -- 链接所需的库。
    -- 对于 MinGW-GCC，pthread 库是原生支持的，只需要链接 "pthread" 即可
    add_links("pthread")

    -- 设置 C 语言标准 (可选，但推荐)
    -- __atomic 原语是 GNU C 扩展，所以使用 gnu11 或 gnu17 标准可能更合适
    set_languages("gnu11")
    -- 或者继续使用 set_languages("c11") 通常也行，因为很多编译器在 C11 模式下也支持 GNU 扩展