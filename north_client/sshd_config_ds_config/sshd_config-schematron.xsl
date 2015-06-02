<?xml version="1.0" standalone="yes"?>
<!--This XSLT was automatically generated from a Schematron schema.-->
<axsl:stylesheet xmlns:date="http://exslt.org/dates-and-times" xmlns:dyn="http://exslt.org/dynamic" xmlns:exsl="http://exslt.org/common" xmlns:math="http://exslt.org/math" xmlns:random="http://exslt.org/random" xmlns:regexp="http://exslt.org/regular-expressions" xmlns:set="http://exslt.org/sets" xmlns:str="http://exslt.org/strings" xmlns:axsl="http://www.w3.org/1999/XSL/Transform" xmlns:sch="http://www.ascc.net/xml/schematron" xmlns:iso="http://purl.oclc.org/dsdl/schematron" xmlns:ss="urn:ietf:params:xml:ns:yang:ssh:sshd_config" xmlns:nc="urn:ietf:params:xml:ns:netconf:base:1.0" extension-element-prefixes="date dyn exsl math random regexp set str" version="1.0"><!--Implementers: please note that overriding process-prolog or process-root is 
    the preferred method for meta-stylesheets to use where possible. -->
<axsl:param name="archiveDirParameter"/><axsl:param name="archiveNameParameter"/><axsl:param name="fileNameParameter"/><axsl:param name="fileDirParameter"/>

<!--PHASES-->


<!--PROLOG-->
<axsl:output xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" xmlns:svrl="http://purl.oclc.org/dsdl/svrl" method="xml" omit-xml-declaration="no" standalone="yes" indent="yes"/>

<!--KEYS-->


<!--DEFAULT RULES-->


<!--MODE: SCHEMATRON-SELECT-FULL-PATH-->
<!--This mode can be used to generate an ugly though full XPath for locators-->
<axsl:template match="*" mode="schematron-select-full-path"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:template>

<!--MODE: SCHEMATRON-FULL-PATH-->
<!--This mode can be used to generate an ugly though full XPath for locators-->
<axsl:template match="*" mode="schematron-get-full-path"><axsl:apply-templates select="parent::*" mode="schematron-get-full-path"/><axsl:text>/</axsl:text><axsl:choose><axsl:when test="namespace-uri()=''"><axsl:value-of select="name()"/><axsl:variable name="p_1" select="1+    count(preceding-sibling::*[name()=name(current())])"/><axsl:if test="$p_1&gt;1 or following-sibling::*[name()=name(current())]">[<axsl:value-of select="$p_1"/>]</axsl:if></axsl:when><axsl:otherwise><axsl:text>*[local-name()='</axsl:text><axsl:value-of select="local-name()"/><axsl:text>' and namespace-uri()='</axsl:text><axsl:value-of select="namespace-uri()"/><axsl:text>']</axsl:text><axsl:variable name="p_2" select="1+   count(preceding-sibling::*[local-name()=local-name(current())])"/><axsl:if test="$p_2&gt;1 or following-sibling::*[local-name()=local-name(current())]">[<axsl:value-of select="$p_2"/>]</axsl:if></axsl:otherwise></axsl:choose></axsl:template><axsl:template match="@*" mode="schematron-get-full-path"><axsl:text>/</axsl:text><axsl:choose><axsl:when test="namespace-uri()=''">@<axsl:value-of select="name()"/></axsl:when><axsl:otherwise><axsl:text>@*[local-name()='</axsl:text><axsl:value-of select="local-name()"/><axsl:text>' and namespace-uri()='</axsl:text><axsl:value-of select="namespace-uri()"/><axsl:text>']</axsl:text></axsl:otherwise></axsl:choose></axsl:template>

<!--MODE: SCHEMATRON-FULL-PATH-2-->
<!--This mode can be used to generate prefixed XPath for humans-->
<axsl:template match="node() | @*" mode="schematron-get-full-path-2"><axsl:for-each select="ancestor-or-self::*"><axsl:text>/</axsl:text><axsl:value-of select="name(.)"/><axsl:if test="preceding-sibling::*[name(.)=name(current())]"><axsl:text>[</axsl:text><axsl:value-of select="count(preceding-sibling::*[name(.)=name(current())])+1"/><axsl:text>]</axsl:text></axsl:if></axsl:for-each><axsl:if test="not(self::*)"><axsl:text/>/@<axsl:value-of select="name(.)"/></axsl:if></axsl:template>

<!--MODE: GENERATE-ID-FROM-PATH -->
<axsl:template match="/" mode="generate-id-from-path"/><axsl:template match="text()" mode="generate-id-from-path"><axsl:apply-templates select="parent::*" mode="generate-id-from-path"/><axsl:value-of select="concat('.text-', 1+count(preceding-sibling::text()), '-')"/></axsl:template><axsl:template match="comment()" mode="generate-id-from-path"><axsl:apply-templates select="parent::*" mode="generate-id-from-path"/><axsl:value-of select="concat('.comment-', 1+count(preceding-sibling::comment()), '-')"/></axsl:template><axsl:template match="processing-instruction()" mode="generate-id-from-path"><axsl:apply-templates select="parent::*" mode="generate-id-from-path"/><axsl:value-of select="concat('.processing-instruction-', 1+count(preceding-sibling::processing-instruction()), '-')"/></axsl:template><axsl:template match="@*" mode="generate-id-from-path"><axsl:apply-templates select="parent::*" mode="generate-id-from-path"/><axsl:value-of select="concat('.@', name())"/></axsl:template><axsl:template match="*" mode="generate-id-from-path" priority="-0.5"><axsl:apply-templates select="parent::*" mode="generate-id-from-path"/><axsl:text>.</axsl:text><axsl:value-of select="concat('.',name(),'-',1+count(preceding-sibling::*[name()=name(current())]),'-')"/></axsl:template><!--MODE: SCHEMATRON-FULL-PATH-3-->
<!--This mode can be used to generate prefixed XPath for humans 
	(Top-level element has index)-->
<axsl:template match="node() | @*" mode="schematron-get-full-path-3"><axsl:for-each select="ancestor-or-self::*"><axsl:text>/</axsl:text><axsl:value-of select="name(.)"/><axsl:if test="parent::*"><axsl:text>[</axsl:text><axsl:value-of select="count(preceding-sibling::*[name(.)=name(current())])+1"/><axsl:text>]</axsl:text></axsl:if></axsl:for-each><axsl:if test="not(self::*)"><axsl:text/>/@<axsl:value-of select="name(.)"/></axsl:if></axsl:template>

<!--MODE: GENERATE-ID-2 -->
<axsl:template match="/" mode="generate-id-2">U</axsl:template><axsl:template match="*" mode="generate-id-2" priority="2"><axsl:text>U</axsl:text><axsl:number level="multiple" count="*"/></axsl:template><axsl:template match="node()" mode="generate-id-2"><axsl:text>U.</axsl:text><axsl:number level="multiple" count="*"/><axsl:text>n</axsl:text><axsl:number count="node()"/></axsl:template><axsl:template match="@*" mode="generate-id-2"><axsl:text>U.</axsl:text><axsl:number level="multiple" count="*"/><axsl:text>_</axsl:text><axsl:value-of select="string-length(local-name(.))"/><axsl:text>_</axsl:text><axsl:value-of select="translate(name(),':','.')"/></axsl:template><!--Strip characters--><axsl:template match="text()" priority="-1"/>

<!--SCHEMA METADATA-->
<axsl:template match="/"><svrl:schematron-output xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" title="" schemaVersion=""><axsl:comment><axsl:value-of select="$archiveDirParameter"/>   
		 <axsl:value-of select="$archiveNameParameter"/>  
		 <axsl:value-of select="$fileNameParameter"/>  
		 <axsl:value-of select="$fileDirParameter"/></axsl:comment><svrl:ns-prefix-in-attribute-values uri="http://exslt.org/dynamic" prefix="dyn"/><svrl:ns-prefix-in-attribute-values uri="urn:ietf:params:xml:ns:yang:ssh:sshd_config" prefix="ss"/><svrl:ns-prefix-in-attribute-values uri="urn:ietf:params:xml:ns:netconf:base:1.0" prefix="nc"/><svrl:active-pattern><axsl:attribute name="id">sshd_config</axsl:attribute><axsl:attribute name="name">sshd_config</axsl:attribute><axsl:apply-templates/></svrl:active-pattern><axsl:apply-templates select="/" mode="M4"/></svrl:schematron-output></axsl:template>

<!--SCHEMATRON PATTERNS-->
<axsl:param name="root" select="/nc:config"/>

<!--PATTERN sshd_config-->


	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:AcceptEnv" priority="1017" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:AcceptEnv"/>

		<!--REPORT -->
<axsl:if test=". = preceding-sibling::ss:AcceptEnv"><svrl:successful-report xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test=". = preceding-sibling::ss:AcceptEnv"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Duplicate leaf-list entry "<axsl:text/><axsl:value-of select="."/><axsl:text/>".</svrl:text></svrl:successful-report></axsl:if>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:AcceptEnv" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:AllowGroups" priority="1016" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:AllowGroups"/>

		<!--REPORT -->
<axsl:if test=". = preceding-sibling::ss:AllowGroups"><svrl:successful-report xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test=". = preceding-sibling::ss:AllowGroups"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Duplicate leaf-list entry "<axsl:text/><axsl:value-of select="."/><axsl:text/>".</svrl:text></svrl:successful-report></axsl:if><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:AuthorizedKeysCommandUser" priority="1015" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:AuthorizedKeysCommandUser"/>

		<!--REPORT -->
<axsl:if test=". = preceding-sibling::ss:AuthorizedKeysCommandUser"><svrl:successful-report xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test=". = preceding-sibling::ss:AuthorizedKeysCommandUser"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Duplicate leaf-list entry "<axsl:text/><axsl:value-of select="."/><axsl:text/>".</svrl:text></svrl:successful-report></axsl:if><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:Banner" priority="1014" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:Banner"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:Banner" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:ClientAliveCountMax" priority="1013" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:ClientAliveCountMax"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:ClientAliveCountMax" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:ClientAliveInterval" priority="1012" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:ClientAliveInterval"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:ClientAliveInterval" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:DebianBanner" priority="1011" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:DebianBanner"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:OS = 'Debian')"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:OS = 'Debian')"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:DebianBanner" is only valid when "../ss:OS = 'Debian'"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:GSSAPIAuthentication" priority="1010" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:GSSAPIAuthentication"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:GSSAPIAuthentication" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:GSSAPIKeyExchange" priority="1009" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:GSSAPIKeyExchange"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:GSSAPIKeyExchange" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:GSSAPICleanupCredentials" priority="1008" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:GSSAPICleanupCredentials"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:GSSAPICleanupCredentials" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:GSSAPIStrictAcceptorCheck" priority="1007" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:GSSAPIStrictAcceptorCheck"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:GSSAPIStrictAcceptorCheck" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:GSSAPIStoreCredentialsOnRekey" priority="1006" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:GSSAPIStoreCredentialsOnRekey"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:GSSAPIStoreCredentialsOnRekey" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:HostbasedAuthentication" priority="1005" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:HostbasedAuthentication"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:HostbasedAuthentication" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:Match" priority="1004" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:Match"/>

		<!--REPORT -->
<axsl:if test=". = preceding-sibling::ss:Match"><svrl:successful-report xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test=". = preceding-sibling::ss:Match"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Duplicate leaf-list entry "<axsl:text/><axsl:value-of select="."/><axsl:text/>".</svrl:text></svrl:successful-report></axsl:if><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:PubkeyAuthentication" priority="1003" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:PubkeyAuthentication"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:PubkeyAuthentication" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:RhostsRSAAuthentication" priority="1002" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:RhostsRSAAuthentication"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 1)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 1)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:RhostsRSAAuthentication" is only valid when "../ss:Protocol = 1"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:RSAAuthentication" priority="1001" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:RSAAuthentication"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 1)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 1)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:RSAAuthentication" is only valid when "../ss:Protocol = 1"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template>

	<!--RULE -->
<axsl:template match="/nc:config/ss:sshd_config_options/ss:Subsystem" priority="1000" mode="M4"><svrl:fired-rule xmlns:svrl="http://purl.oclc.org/dsdl/svrl" context="/nc:config/ss:sshd_config_options/ss:Subsystem"/>

		<!--ASSERT -->
<axsl:choose><axsl:when test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"/><axsl:otherwise><svrl:failed-assert xmlns:svrl="http://purl.oclc.org/dsdl/svrl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:schold="http://www.ascc.net/xml/schematron" test="ancestor-or-self::*[processing-instruction('dsrl')] or (../ss:Protocol = 2)"><axsl:attribute name="location"><axsl:apply-templates select="." mode="schematron-get-full-path"/></axsl:attribute><svrl:text>Node "ss:Subsystem" is only valid when "../ss:Protocol = 2"</svrl:text></svrl:failed-assert></axsl:otherwise></axsl:choose><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template><axsl:template match="text()" priority="-1" mode="M4"/><axsl:template match="@*|node()" priority="-2" mode="M4"><axsl:apply-templates select="*|comment()|processing-instruction()" mode="M4"/></axsl:template></axsl:stylesheet>
