-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- 主机： localhost
-- 生成日期： 2020-01-02 17:22:57
-- 服务器版本： 5.7.26
-- PHP 版本： 7.3.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 数据库： `shirley_database`
--

-- --------------------------------------------------------

--
-- 表的结构 `blog_article`
--

CREATE TABLE `blog_article` (
  `id` int(10) UNSIGNED NOT NULL COMMENT '文章id',
  `title` varchar(250) NOT NULL COMMENT '文章标题',
  `summary` varchar(2048) NOT NULL COMMENT '文章摘要',
  `category` int(10) UNSIGNED NOT NULL COMMENT '文章分类',
  `body` text NOT NULL COMMENT '文章正文',
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '发布时间'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- 表的结构 `blog_category`
--

CREATE TABLE `blog_category` (
  `id` int(10) UNSIGNED NOT NULL COMMENT '分类ID',
  `name` varchar(120) COLLATE utf8_unicode_ci NOT NULL COMMENT '分类名称'
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 转储表的索引
--

--
-- 表的索引 `blog_article`
--
ALTER TABLE `blog_article`
  ADD PRIMARY KEY (`id`),
  ADD KEY `title` (`title`),
  ADD KEY `category` (`category`);

--
-- 表的索引 `blog_category`
--
ALTER TABLE `blog_category`
  ADD PRIMARY KEY (`id`);

--
-- 在导出的表使用AUTO_INCREMENT
--

--
-- 使用表AUTO_INCREMENT `blog_article`
--
ALTER TABLE `blog_article`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '文章id';

--
-- 使用表AUTO_INCREMENT `blog_category`
--
ALTER TABLE `blog_category`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '分类ID';
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
