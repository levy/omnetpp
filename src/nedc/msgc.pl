#
# msgc.pl: supports message subclassing: compiles NED files with message
# declarations into C++ code.
#
# This perl script is a temporary solution until new nedc is ready.
#

$filename = $ARGV[0];
$filename =~ /./ || die "*** no file name given\n";
$filename =~ /\.[^\/]*$/ || die "*** file name must contain a dot\n";
$hfile = $filename;
$hfile =~ s/\.[^.]*$/_n.h/;
$ccfile = $filename;
$ccfile =~ s/\.[^.]*$/_n.cc/;

$msg = "";
open(IN,$filename) || die "*** cannot open input file $filename";
while (<IN>)
{
    s|//.*$||;
    $msg .= $_;
}
close(IN);

open(H,">$hfile") || die "*** cannot open output file $hfile";
open(CC,">$ccfile") || die "*** cannot open output file $ccfile";

print H "//\n// TBD: add copyright stuff, includes here\n//\n\n";
print H "#include <omnetpp.h>\n";
print CC "//\n// TBD: add copyright stuff, includes here\n//\n\n";
print CC "#include \"$hfile\"\n\n";

# pre-register some OMNeT++ classes so that one doesn't need to announce them
@classes = ('cObject', 'cMessage', 'cPacket');
foreach $class (@classes) {
    $classtype{$class} = 'cobject';
    $hasdescriptor{$class} = 0;
}

@enums = ();

# parse cppincludes
while ($msg =~ s/cppinclude\s+(["\<].*?["\>])//s)
{
    print H "#include $1\n";
}
print H "\n";

# parse type announcements in ned text
while ($msg =~ s/(struct|cobject|noncobject)\s+([^\s]*)\s*;//s)
{
    $class = $2;
    $classtype{$class} = $1; # 'struct' or 'cobject' or 'noncobject'
    $hasdescriptor{$class} = 0;
    push(@classes, $class);
}

# parse enums in ned text
while ($msg =~ s/enum\s+(.+?)\s*{(.*?)};?//s)
{
    $enumhdr = $1;
    $fields = $2;

    if ($enumhdr =~ /^([^\s]+?)\s*updates\s*([^\s]+?)$/s)
    {
        $enumname = $1;
        $updateenum = $2;
    }
    elsif ($enumhdr =~ /^([^\s]+?)$/s)
    {
        $enumname = $enumhdr;
        $updateenum = '';
    }
    else
    {
        $enumhdr =~ s/\s+/ /sg;
        print STDERR "*** invalid enum declaration syntax '$enumhdr'\n";
        $enumname = "???";
        $updateenum = '';
    }

    @fieldlist = ();
    undef %fval;

    #
    # parse enum { ... } syntax
    #
    $crap = '';
    while ($fields =~ s/^(.*?);//s)
    {
        $field = $1;

        # value
        if ($field =~ s/=\s*(.*?)\s*$//s) {
            $fieldvalue = $1;
        } else {
            $fieldvalue = '';
        }

        # identifier
        if ($field =~ /^\s*([A-Za-z0-9_]+)\s*$/s) {
            $fieldname = $1;
        } else {
            $crap .= $field;
            print STDERR "*** missing identifier name in enum $enumname\n";
        }

        # store field
        push(@fieldlist,$fieldname);
        $fval{$fieldname}=$fieldvalue;

    }
    $crap .= $fields;
    if ($crap =~ /[^\s]/s) {
        $crap =~ s/\n\n+/\n\n/sg;
        $crap =~ s/^\n//s;
        $crap =~ s/\n$//s;
        print STDERR "*** some parts not understood in enum $enumname:\n";
        print STDERR "'$crap'\n";
    }

    #
    # generate code
    #
    if (grep(/^\Q$enumname\E$/,@enums)) {
        print STDERR "*** enum '$enumname' already defined\n";
    }
    push(@enums, $enumname);

    print H "enum $enumname {\n";
    foreach $fieldname (@fieldlist)
    {
        print H "    $fieldname = $fval{$fieldname},\n";
    }
    print H "};\n\n";
    print CC "static sEnumBuilder _$enumname( \"$enumname\",\n";
    foreach $fieldname (@fieldlist)
    {
        print CC "    $fieldname, \"$fieldname\",\n";
    }
    print CC "    0, NULL\n";
    print CC ");\n\n";

    if ($updateenum ne '')
    {
        print CC "static sEnumBuilder _${updateenum}_${enumname}( \"$updateenum\",\n";
        foreach $fieldname (@fieldlist)
        {
            print CC "    $fieldname, \"$fieldname\",\n";
        }
        print CC "    0, NULL\n";
        print CC ");\n\n";
    }
}

# parse message/class/struct definitions
while ($msg =~ s/(message|class|struct)\s+(.+?)\s*{(.*?)};?//s)
{
    # reset
    @fieldlist = ();
    @proplist = ();
    undef %pval;

    #
    # parse message { ... } syntax
    #
    $keyword = $1;  # 'message' or 'class' or 'struct'
    $msghdr = $2;   # must be "<name>" or "<name> extends <name>"
    $body = $3;

    if ($msghdr =~ /^([^\s]+?)\s*extends\s*([^\s]+?)$/s)
    {
        $msgname = $1;
        $msgbase = $2;
    }
    elsif ($msghdr =~ /^([^\s]+?)$/s)
    {
        $msgname = $msghdr;
        $msgbase = '';
    }
    else
    {
        $msghdr =~ s/\s+/ /sg;
        print STDERR "*** invalid message declaration syntax '$msghdr'\n";
        $msgname = "???";
        $msgbase = '';
    }

    #
    # process "properties:"
    #
    $crap = '';
    if ($body =~ /properties:(.*)$/s)
    {
        $properties = $1;
        $properties =~ s/fields:.*$//s;  # cut off fields section
        while ($properties =~ s/^(.*?);//s)
        {
            $prop = $1;
            if ($prop =~ /^\s*(.*?)\s*=\s*(.*?)\s*$/s)
            {
                $propname = $1;
                $propvalue = $2;
                push(@proplist,$propname);
                $pval{$propname} = $propvalue;
            }
            else {$crap.=$prop;}
        }
        $crap.=$properties;
        if ($crap =~ /[^\s]/s)
        {
            $crap =~ s/\n\n+/\n\n/sg;
            $crap =~ s/^\n//s;
            $crap =~ s/\n$//s;
            print STDERR "*** some parts not understood in 'properties' section of message $msgname:\n";
            print STDERR "'$crap'\n";
        }
    }

    #
    # process "fields:"
    #
    $crap = '';
    if ($body =~ /fields:(.*)$/s)
    {
        $fields = $1;
        while ($fields =~ s/^(.*?);//s)
        {
            $field = $1;

            # virtual
            if ($field =~ s/^\s*virtual\s+//s) {
                $isvirtual = 1;
            } else {
                $isvirtual = 0;
            }

            # enum
            if ($field =~ s/enum\s*\((.*?)\)\s*$//s) {
                $fieldenum = $1;
            } else {
                $fieldenum = '';
            }

            # default value
            if ($field =~ s/=\s*(.*?)\s*$//s) {
                $fieldvalue = $1;
            } else {
                $fieldvalue = '';
            }

            # array
            if ($field =~ s/\[\s*(.*?)\s*\]\s*$//s) {
                $isarray = 1;
                $arraysize = $1;
                if ($arraysize !~ /^[0-9]*$/) {
                    print STDERR "*** array size must be numeric (not '$arraysize') message $msgname\n";
                }
            } else {
                $isarray = 0;
                $arraysize = '';
            }

            # type fieldname
            if ($field =~ /^\s*(.+?)\s*([A-Za-z0-9_]+)\s*$/s)
            {
                $fieldtype = $1;
                $fieldname = $2;
                $fieldtype =~ s/\s+/ /sg;

                push(@fieldlist,$fieldname);
                $ftype{$fieldname} = $fieldtype;
                $fval{$fieldname} = $fieldvalue;
                $fisvirtual{$fieldname} = $isvirtual;
                $fisarray{$fieldname} = $isarray;
                $farraysize{$fieldname} = $arraysize;
                $fenumname{$fieldname} = $fieldenum;
                #print "$fieldname: $ftype{$fieldname} =$fval{$fieldname}  []:$fisarray{$fieldname}  [$farraysize{$fieldname}]\n";
            }
            else {$crap.=$field;}
        }
        $crap.=$fields;
        if ($crap =~ /[^\s]/s)
        {
            $crap =~ s/\n\n+/\n\n/sg;
            $crap =~ s/^\n//s;
            $crap =~ s/\n$//s;
            print STDERR "*** some parts not understood in 'fields' section of message $msgname:\n";
            print STDERR "'$crap'\n";
        }
    }
    else
    {
        print STDERR "*** no 'fields' section in message $msgname\n";
        next;
    }


    #
    # prepare for code generation
    #
    if (grep(/^\Q$msgname\E$/,@classes)) {
        print STDERR "*** class '$msgname' already defined\n";
    }
    if ($msgbase eq '') {
        if ($keyword eq 'message') {
            $classtype = 'cobject';
        } elsif ($keyword eq 'class') {
            $classtype = 'noncobject';
        } elsif ($keyword eq 'struct') {
            $classtype = 'struct';
        } else {
            die 'internal error';
        }
    } else {
        if (!grep(/^\Q$msgbase\E$/,@classes)) {
            print STDERR "*** unknown base class '$msgbase'\n";
        }
        $classtype = $classtype{$msgbase};
    }

    # register this class
    push(@classes, $msgname);
    $classtype{$msgname} = $classtype;
    $hasdescriptor{$msgname} = 1;

    #
    # produce all sorts of derived names
    #
    if ($pval{"customize"} eq "true") {
        $gap = 1;
        $msgclass = $msgname."_Base";
        $realmsgclass = $msgname;
        $msgdescclass = $realmsgclass."Descriptor";
    } else {
        $gap = 0;
        $msgclass = $msgname;
        $realmsgclass = $msgclass;
        $msgdescclass = $msgclass."Descriptor";
    }
    if ($msgbase eq '') {
        if ($keyword eq 'message') {
            $msgbaseclass = 'cMessage';
        } elsif ($keyword eq 'class') {
            $msgbaseclass = 'cObject';
        } elsif ($keyword eq 'struct') {
            $msgbaseclass = '';
        } else {
            die 'internal error';
        }
    } else {
        $msgbaseclass = $msgbase;
    }

    $hasbasedescriptor = $hasdescriptor{$msgbaseclass};
    if ($hasbasedescriptor) {
        $msgbasedescclass = $msgbaseclass."Descriptor";
    } else {
        $msgbasedescclass = "cStructDescriptor";
    }

    foreach $fieldname (@fieldlist)
    {
        if ($fisvirtual{$fieldname} && !$gap) {
            print STDERR "*** virtual fields assume 'customize=true' property in message $msgname\n";
        }
        $var{$fieldname} = $fieldname;
        $varsize{$fieldname} = $var{$fieldname}."_arraysize";
        $capfieldname = $fieldname;
        $capfieldname =~ s/(.)(.*)/uc($1).$2/e;
        $getter{$fieldname} = "get".$capfieldname;
        $setter{$fieldname} = "set".$capfieldname;
        $alloc{$fieldname} = "set".$capfieldname."ArraySize";
        $getsize{$fieldname} = "get".$capfieldname."ArraySize";

        $ftype = $ftype{$fieldname};
        if ($ftype =~ /^(.*?)\s*\*$/) {
            $ftype = $1;
            $fpointer = 1;
            print STDERR "*** pointers not supported yet in message $msgname\n";
        } else {
            $fpointer = 0;
        }

        if (grep(/^\Q$ftype\E$/,@classes)) {
            $fkind{$fieldname} = 'struct';
        } else {
            $fkind{$fieldname} = 'basic';
        }

        if ($fkind{$fieldname} eq 'struct') {
            $datatype{$fieldname} = $ftype;
            $argtype{$fieldname} = "const $ftype&";
            $tostring{$fieldname} = "${ftype}2string";
            $fromstring{$fieldname} = "string2${ftype}";
            #$fval{$fieldname} = '' unless ($fval{$fieldname} ne '');
        } elsif ($fkind{$fieldname} eq 'basic') {
            if ($ftype eq "bool") {
                $datatype{$fieldname} = "bool";
                $argtype{$fieldname} = "bool";
                $tostring{$fieldname} = "bool2string";
                $fromstring{$fieldname} = "string2bool";
                $fval{$fieldname} = 'false' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "char") {
                $datatype{$fieldname} = "char";
                $argtype{$fieldname} = "char";
                $tostring{$fieldname} = "long2string";
                $fromstring{$fieldname} = "string2long";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "unsigned char") {
                $datatype{$fieldname} = "unsigned char";
                $argtype{$fieldname} = "unsigned char";
                $tostring{$fieldname} = "long2string";
                $fromstring{$fieldname} = "string2long";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "short") {
                $datatype{$fieldname} = "short";
                $argtype{$fieldname} = "short";
                $tostring{$fieldname} = "long2string";
                $fromstring{$fieldname} = "string2long";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "unsigned short") {
                $datatype{$fieldname} = "unsigned short";
                $argtype{$fieldname} = "unsigned short";
                $tostring{$fieldname} = "long2string";
                $fromstring{$fieldname} = "string2long";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "int") {
                $datatype{$fieldname} = "int";
                $argtype{$fieldname} = "int";
                $tostring{$fieldname} = "long2string";
                $fromstring{$fieldname} = "string2long";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "unsigned int") {
                $datatype{$fieldname} = "unsigned int";
                $argtype{$fieldname} = "unsigned int";
                $tostring{$fieldname} = "long2string";
                $fromstring{$fieldname} = "string2long";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "long") {
                $datatype{$fieldname} = "long";
                $argtype{$fieldname} = "long";
                $tostring{$fieldname} = "long2string";
                $fromstring{$fieldname} = "string2long";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "unsigned long") {
                $datatype{$fieldname} = "unsigned long";
                $argtype{$fieldname} = "unsigned long";
                $tostring{$fieldname} = "long2string";
                $fromstring{$fieldname} = "string2long";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "double") {
                $datatype{$fieldname} = "double";
                $argtype{$fieldname} = "double";
                $tostring{$fieldname} = "double2string";
                $fromstring{$fieldname} = "string2double";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            } elsif ($ftype eq "string") {
                $datatype{$fieldname} = "opp_string";
                $argtype{$fieldname} = "const char *";
                $tostring{$fieldname} = "oppstring2string";
                $fromstring{$fieldname} = "opp_string";
                $fval{$fieldname} = '""' unless ($fval{$fieldname} ne '');
            } else {
                print STDERR "*** unknown data type '$ftype' (is it struct?)\n";
                $datatype{$fieldname} = $ftype;
                $argtype{$fieldname} = $ftype;
                $tostring{$fieldname} = "";
                $fromstring{$fieldname} = "";
                $fval{$fieldname} = '0' unless ($fval{$fieldname} ne '');
            }
        } elsif ($fkind{$fieldname} eq 'special') {
            # ***********FIXME******  ???
        } else {
            die 'internal error';
        }
    }

    #
    # print class
    #
    if ($msgbaseclass eq "") {
        print H "class $msgclass\n";
    } else {
        print H "class $msgclass : public $msgbaseclass\n";
    }
    print H "{\n";
    print H "  protected:\n";
    foreach $fieldname (@fieldlist)
    {
        if (!$fisvirtual{$fieldname}) {
            if ($fisarray{$fieldname} && $farraysize{$fieldname} ne '') {
                print H "    $datatype{$fieldname} $var{$fieldname}\[$farraysize{$fieldname}\];\n";
            } elsif ($fisarray{$fieldname} && $farraysize{$fieldname} eq '') {
                print H "    $datatype{$fieldname} *$var{$fieldname}; // array ptr\n";
                print H "    unsigned $varsize{$fieldname};\n";
            } else {
                print H "    $datatype{$fieldname} $var{$fieldname};\n";
            }
        }
    }
    if ($gap) {
        print H "    // make constructors protected to avoid instantiation\n";
    } else {
        print H "  public:\n";
    }
    if ($classtype eq "cobject") {
        print H "    $msgclass(const char *name=NULL);\n";
    } else {
        print H "    $msgclass();\n";
    }
    print H "    $msgclass(const $msgclass& other);\n";
    if ($gap) {
        print H "  public:\n";
    }
    print H "    virtual ~$msgclass();\n";
    if ($classtype eq "cobject") {
        print H "    virtual const char *className() const {return \"$realmsgclass\";}\n";
    }
    print H "    $msgclass& operator=(const $msgclass& other);\n";
    if ($classtype eq "cobject" && !$gap) {
        print H "    virtual cObject *dup() const {return new $msgclass(*this);}\n";
    }
    print H "\n";
    print H "    // field getter/setter methods\n";
    foreach $fieldname (@fieldlist)
    {
        if ($fisvirtual{$fieldname}) {
            $pure = ' = 0';
        } else {
            $pure = '';
        }
        if ($fisarray{$fieldname} && $farraysize{$fieldname} ne '') {
            print H "    virtual unsigned $getsize{$fieldname}() const$pure;\n";
            print H "    virtual $argtype{$fieldname} $getter{$fieldname}(unsigned k) const$pure;\n";
            print H "    virtual void $setter{$fieldname}(unsigned k, $argtype{$fieldname} $var{$fieldname})$pure;\n";
        } elsif ($fisarray{$fieldname} && $farraysize{$fieldname} eq '') {
            print H "    virtual void $alloc{$fieldname}(unsigned size)$pure;\n";
            print H "    virtual unsigned $getsize{$fieldname}() const$pure;\n";
            print H "    virtual $argtype{$fieldname} $getter{$fieldname}(unsigned k) const$pure;\n";
            print H "    virtual void $setter{$fieldname}(unsigned k, $argtype{$fieldname} $var{$fieldname})$pure;\n";
        } else {
            print H "    virtual $argtype{$fieldname} $getter{$fieldname}() const$pure;\n";
            print H "    virtual void $setter{$fieldname}($argtype{$fieldname} $var{$fieldname})$pure;\n";
        }
    }
    print H "};\n\n";

    if ($gap)
    {
        print H "/*\n";
        print H "* The minimum code to be written for $realmsgclass:\n";
        print H "* (methods that cannot be inherited from $msgclass)\n";
        print H "*\n";
        print H "* class $realmsgclass : public $msgclass\n";
        print H "* {\n";
        print H "*   public:\n";
        if ($classtype eq "cobject") {
            print H "*     $realmsgclass(const char *name=NULL) : $msgclass(name) {}\n";
        } else {
            print H "*     $realmsgclass() : $msgclass() {}\n";
        }
        print H "*     $realmsgclass(const $realmsgclass& other) : $msgclass(other) {}\n";
        print H "*     $realmsgclass& operator=(const $realmsgclass& other) {$msgclass\:\:operator=(other); return *this;}\n";
        if ($classtype eq "cobject") {
            print H "*     virtual cObject *dup() {return new $realmsgclass(*this);}\n";
        }
        print H "* };\n";
        if ($classtype eq "cobject") {
            print H "* Register_Class($realmsgclass);\n";
        }
        print H "*/\n\n";
    }

    if ($classtype eq "cobject" && !$gap) {
        print CC "Register_Class($msgclass);\n\n";
    }

    if ($classtype eq "cobject") {
        if ($msgbaseclass eq "") {
            print CC "$msgclass\:\:$msgclass(const char *name)\n";
        } else {
            print CC "$msgclass\:\:$msgclass(const char *name) : $msgbaseclass(name)\n";
        }
    } else {
        if ($msgbaseclass eq "") {
            print CC "$msgclass\:\:$msgclass()\n";
        } else {
            print CC "$msgclass\:\:$msgclass() : $msgbaseclass()\n";
        }
    }
    print CC "{\n";
    foreach $fieldname (@fieldlist)
    {
        if (!$fisvirtual{$fieldname}) {
            if ($fisarray{$fieldname} && $farraysize{$fieldname} ne '') {
                if ($fval{$fieldname} ne '') {
                    print CC "    for (int i=0; i<$farraysize{$fieldname}; i++)\n";
                    print CC "        $var{$fieldname}\[i\] = 0;\n";
                }
            } elsif ($fisarray{$fieldname} && $farraysize{$fieldname} eq '') {
                print CC "    $varsize{$fieldname} = 0;\n";
                print CC "    $var{$fieldname} = 0;\n";
            } else {
                if ($fval{$fieldname} ne '') {
                    print CC "    $var{$fieldname} = $fval{$fieldname};\n";
                }
            }
        }
    }
    print CC "}\n\n";
    if ($msgbaseclass eq "") {
        print CC "$msgclass\:\:$msgclass(const $msgclass& other)\n";
    } else {
        print CC "$msgclass\:\:$msgclass(const $msgclass& other) : $msgbaseclass()\n";
    }
    print CC "{\n";
    if ($classtype eq "cobject") {
        print CC "    setName(other.name());\n";
    }
    foreach $fieldname (@fieldlist)
    {
        if (!$fisvirtual{$fieldname}) {
            if ($fisarray{$fieldname} && $farraysize{$fieldname} eq '') {
                print CC "    $varsize{$fieldname} = 0;\n";
                print CC "    $var{$fieldname} = 0;\n";
            }
        }
    }
    print CC "    operator=(other);\n";
    print CC "}\n\n";
    print CC "$msgclass\:\:~$msgclass()\n";
    print CC "{\n";
    foreach $fieldname (@fieldlist)
    {
        if (!$fisvirtual{$fieldname}) {
            if ($fisarray{$fieldname} && $farraysize{$fieldname} eq '') {
                print CC "    delete [] $var{$fieldname};\n";
            }
        }
    }
    print CC "}\n\n";
    print CC "$msgclass& $msgclass\:\:operator=(const $msgclass& other)\n";
    print CC "{\n";
    print CC "    if (this==&other) return *this;\n";
    if ($msgbaseclass ne "") {
        print CC "    $msgbaseclass\:\:operator=(other);\n";
    }
    foreach $fieldname (@fieldlist)
    {
        if (!$fisvirtual{$fieldname}) {
            if ($fisarray{$fieldname} && $farraysize{$fieldname} ne '') {
                print CC "    for (int i=0; i<$farraysize{$fieldname}; i++)\n";
                print CC "        $var{$fieldname}\[i\] = other.$var{$fieldname}\[i\];\n";
            } elsif ($fisarray{$fieldname} && $farraysize{$fieldname} eq '') {
                print CC "    delete [] $var{$fieldname};\n";
                print CC "    $var{$fieldname} = new $datatype{$fieldname}\[other.$varsize{$fieldname}\];\n";
                print CC "    $varsize{$fieldname} = other.$varsize{$fieldname};\n";
                print CC "    for (int i=0; i<$varsize{$fieldname}; i++)\n";
                print CC "        $var{$fieldname}\[i\] = other.$var{$fieldname}\[i\];\n";
            } else {
                print CC "    $var{$fieldname} = other.$var{$fieldname};\n";
            }
        }
    }
    print CC "    return *this;\n";
    print CC "}\n\n";

    foreach $fieldname (@fieldlist)
    {
        if (!$fisvirtual{$fieldname}) {
            if ($fisarray{$fieldname} && $farraysize{$fieldname} ne '') {
                print CC "unsigned $msgclass\:\:$getsize{$fieldname}() const\n";
                print CC "{\n";
                print CC "    return $farraysize{$fieldname};\n";
                print CC "}\n\n";
                print CC "$argtype{$fieldname} $msgclass\:\:$getter{$fieldname}(unsigned k) const\n";
                print CC "{\n";
                print CC "    if (k>=$farraysize{$fieldname}) return 0;\n";
                print CC "    return $var{$fieldname}\[k\];\n";
                print CC "}\n\n";
                print CC "void $msgclass\:\:$setter{$fieldname}(unsigned k, $argtype{$fieldname} $var{$fieldname})\n";
                print CC "{\n";
                print CC "    if (k>=$farraysize{$fieldname}) return;\n";
                print CC "    this->$var{$fieldname}\[k\] = $var{$fieldname};\n";
                print CC "}\n\n";
            } elsif ($fisarray{$fieldname} && $farraysize{$fieldname} eq '') {
                print CC "void $msgclass\:\:$alloc{$fieldname}(unsigned size)\n";
                print CC "{\n";
                print CC "    $datatype{$fieldname} *$var{$fieldname}2 = new $datatype{$fieldname}\[size\];\n";
                print CC "    unsigned sz = $varsize{$fieldname} > size ? $varsize{$fieldname} : size;\n";
                print CC "    for (int i=0; i<sz; i++)\n";
                print CC "        $var{$fieldname}2\[i\] = $var{$fieldname}\[i\];\n";
                print CC "    for (int i=sz; i<size; i++)\n";
                print CC "        $var{$fieldname}2\[i\] = 0;\n";
                print CC "    $varsize{$fieldname} = size;\n";
                print CC "    delete [] $var{$fieldname};\n";
                print CC "    $var{$fieldname} = $var{$fieldname}2;\n";
                print CC "}\n\n";
                print CC "unsigned $msgclass\:\:$getsize{$fieldname}() const\n";
                print CC "{\n";
                print CC "    return $varsize{$fieldname};\n";
                print CC "}\n\n";
                print CC "$argtype{$fieldname} $msgclass\:\:$getter{$fieldname}(unsigned k) const\n";
                print CC "{\n";
                print CC "    if (k>=$varsize{$fieldname}) return 0;\n";
                print CC "    return $var{$fieldname}\[k\];\n";
                print CC "}\n\n";
                print CC "void $msgclass\:\:$setter{$fieldname}(unsigned k, $argtype{$fieldname} $var{$fieldname})\n";
                print CC "{\n";
                print CC "    if (k>=$varsize{$fieldname}) return;\n";
                print CC "    this->$var{$fieldname}\[k\]=$var{$fieldname};\n";
                print CC "}\n\n";
            } else {
                print CC "$argtype{$fieldname} $msgclass\:\:$getter{$fieldname}() const\n";
                print CC "{\n";
                print CC "    return $var{$fieldname};\n";
                print CC "}\n\n";
                print CC "void $msgclass\:\:$setter{$fieldname}($argtype{$fieldname} $var{$fieldname})\n";
                print CC "{\n";
                print CC "    this->$var{$fieldname} = $var{$fieldname};\n";
                print CC "}\n\n";
            }
        }
    }

    #
    # print descriptor class
    #
    print CC "class $msgdescclass : public $msgbasedescclass\n";
    print CC "{\n";
    print CC "  public:\n";
    print CC "    $msgdescclass(void *p);\n";
    print CC "    virtual ~$msgdescclass();\n";
    print CC "    virtual const char *className() const {return \"$msgdescclass\";}\n";
    print CC "    $msgdescclass& operator=(const $msgdescclass& other);\n";
    print CC "    virtual cObject *dup() const {return new $msgdescclass(*this);}\n";


    print CC "\n";
    print CC "    virtual int getFieldCount();\n";
    print CC "    virtual const char *getFieldName(int field);\n";
    print CC "    virtual int getFieldType(int field);\n";
    print CC "    virtual const char *getFieldTypeString(int field);\n";
    print CC "    virtual const char *getFieldEnumName(int field);\n";
    print CC "    virtual int getArraySize(int field);\n";
    print CC "\n";
    print CC "    virtual bool getFieldAsString(int field, int i, char *resultbuf, int bufsize);\n";
    print CC "    virtual bool setFieldAsString(int field, int i, const char *value);\n";
    print CC "\n";
    print CC "    virtual const char *getFieldStructName(int field);\n";
    print CC "    virtual void *getFieldStructPointer(int field, int i);\n";
    print CC "};\n\n";

    # register class
    print CC "Register_Class($msgdescclass);\n\n";

    # ctor, dtor
    $fieldcount = $#fieldlist+1;
    print CC "$msgdescclass\:\:$msgdescclass(void *p) : $msgbasedescclass(p)\n";
    print CC "{\n";
    print CC "}\n";
    print CC "\n";

    print CC "$msgdescclass\:\:~$msgdescclass()\n";
    print CC "{\n";
    print CC "}\n";
    print CC "\n";

    # getFieldCount()
    print CC "int $msgdescclass\:\:getFieldCount()\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    return $msgbasedescclass\:\:getFieldCount() + $fieldcount;\n";
    } else {
        print CC "    return $fieldcount;\n";
    }
    print CC "}\n";
    print CC "\n";

    # getFieldType()
    print CC "int $msgdescclass\:\:getFieldType(int field)\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    if (field < $msgbasedescclass\:\:getFieldCount())\n";
        print CC "        return $msgbasedescclass\:\:getFieldType(field);\n";
        print CC "    field -= $msgbasedescclass\:\:getFieldCount();\n";
    }
    print CC "    switch (field) {\n";
    for ($i=0; $i<$fieldcount; $i++)
    {
        if ($fisarray{$fieldlist[$i]}) {
            $arr = '_ARRAY';
        } else {
            $arr = '';
        }
        if ($fkind{$fieldlist[$i]} eq 'basic') {
            print CC "        case $i: return FT_BASIC${arr};\n";
        } elsif ($fkind{$fieldlist[$i]} eq 'struct') {
            print CC "        case $i: return FT_STRUCT${arr};\n";
        } elsif ($fkind{$fieldlist[$i]} eq 'special') {
            print CC "        case $i: return FT_SPECIAL${arr};\n";
        } else {
            die 'internal error';
        }
    }
    print CC "        default: return FT_INVALID;\n";
    print CC "    }\n";
    print CC "}\n";
    print CC "\n";

    # getFieldName()
    print CC "const char *$msgdescclass\:\:getFieldName(int field)\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    if (field < $msgbasedescclass\:\:getFieldCount())\n";
        print CC "        return $msgbasedescclass\:\:getFieldName(field);\n";
        print CC "    field -= $msgbasedescclass\:\:getFieldCount();\n";
    }
    print CC "    switch (field) {\n";
    for ($i=0; $i<$fieldcount; $i++)
    {
        print CC "        case $i: return \"$fieldlist[$i]\";\n";
    }
    print CC "        default: return NULL;\n";
    print CC "    }\n";
    print CC "}\n";
    print CC "\n";

    # getFieldTypeString()
    print CC "const char *$msgdescclass\:\:getFieldTypeString(int field)\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    if (field < $msgbasedescclass\:\:getFieldCount())\n";
        print CC "        return $msgbasedescclass\:\:getFieldTypeString(field);\n";
        print CC "    field -= $msgbasedescclass\:\:getFieldCount();\n";
    }
    print CC "    switch (field) {\n";
    for ($i=0; $i<$fieldcount; $i++)
    {
        print CC "        case $i: return \"$ftype{$fieldlist[$i]}\";\n";
    }
    print CC "        default: return NULL;\n";
    print CC "    }\n";
    print CC "}\n";
    print CC "\n";

    # getFieldEnumName()
    print CC "const char *$msgdescclass\:\:getFieldEnumName(int field)\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    if (field < $msgbasedescclass\:\:getFieldCount())\n";
        print CC "        return $msgbasedescclass\:\:getFieldEnumName(field);\n";
        print CC "    field -= $msgbasedescclass\:\:getFieldCount();\n";
    }
    print CC "    switch (field) {\n";
    for ($i=0; $i<$fieldcount; $i++)
    {
        if ($fenumname{$fieldlist[$i]} ne '') {
            print CC "        case $i: return \"$fenumname{$fieldlist[$i]}\";\n";
        }
    }
    print CC "        default: return NULL;\n";
    print CC "    }\n";
    print CC "}\n";
    print CC "\n";

    # getArraySize()
    print CC "int $msgdescclass\:\:getArraySize(int field)\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    if (field < $msgbasedescclass\:\:getFieldCount())\n";
        print CC "        return $msgbasedescclass\:\:getArraySize(field);\n";
        print CC "    field -= $msgbasedescclass\:\:getFieldCount();\n";
    }
    print CC "    switch (field) {\n";
    for ($i=0; $i<$fieldcount; $i++) {
        if ($fisarray{$fieldlist[$i]} && $farraysize{$fieldlist[$i]} ne '') {
            print CC "        case $i: return $farraysize{$fieldlist[$i]};\n";
        } elsif ($fisarray{$fieldlist[$i]} && $farraysize{$fieldlist[$i]} eq '') {
            print CC "        case $i: return $varsize{$fieldlist[$i]};\n";
        }
    }
    print CC "        default: return 0;\n";
    print CC "    }\n";
    print CC "}\n";
    print CC "\n";

    print CC "bool $msgdescclass\:\:getFieldAsString(int field, int i, char *resultbuf, int bufsize)\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    if (field < $msgbasedescclass\:\:getFieldCount())\n";
        print CC "        return $msgbasedescclass\:\:getFieldAsString(field,i,resultbuf,bufsize);\n";
        print CC "    field -= $msgbasedescclass\:\:getFieldCount();\n";
    }
    print CC "    $msgclass *pp = ($msgclass *)p;\n";
    print CC "    switch (field) {\n";
    for ($i=0; $i<$fieldcount; $i++)
    {
        if ($fkind{$fieldlist[$i]} eq 'basic') {
            if ($fisarray{$fieldlist[$i]}) {
                print CC "        case $i: $tostring{$fieldlist[$i]}(pp->$getter{$fieldlist[$i]}(i),resultbuf,bufsize); return true;\n";
            } else {
                print CC "        case $i: $tostring{$fieldlist[$i]}(pp->$getter{$fieldlist[$i]}(),resultbuf,bufsize); return true;\n";
            }
        } elsif ($fkind{$fieldlist[$i]} eq 'struct') {
            print CC "        case $i: return false;\n";
        } elsif ($fkind{$fieldlist[$i]} eq 'special') {
            print CC "        case $i: return false; //TBD!!!\n";
        } else {
            die 'internal error';
        }
    }
    print CC "        default: return false;\n";
    print CC "    }\n";
    print CC "}\n";
    print CC "\n";

    print CC "bool $msgdescclass\:\:setFieldAsString(int field, int i, const char *value)\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    if (field < $msgbasedescclass\:\:getFieldCount())\n";
        print CC "        return $msgbasedescclass\:\:setFieldAsString(field,i,value);\n";
        print CC "    field -= $msgbasedescclass\:\:getFieldCount();\n";
    }
    print CC "    $msgclass *pp = ($msgclass *)p;\n";
    print CC "    switch (field) {\n";
    for ($i=0; $i<$fieldcount; $i++)
    {
        if ($fkind{$fieldlist[$i]} eq 'basic') {
            if ($fisarray{$fieldlist[$i]}) {
                print CC "        case $i: pp->$setter{$fieldlist[$i]}($fromstring{$fieldlist[$i]}(value),i); return true;\n";
            } else {
                print CC "        case $i: pp->$setter{$fieldlist[$i]}($fromstring{$fieldlist[$i]}(value)); return true;\n";
            }
        } elsif ($fkind{$fieldlist[$i]} eq 'struct') {
            print CC "        case $i: return false;\n";
        } elsif ($fkind{$fieldlist[$i]} eq 'special') {
            print CC "        case $i: return false; //TBD!!!\n";
        } else {
            die 'internal error';
        }
    }
    print CC "        default: return false;\n";
    print CC "    }\n";
    print CC "}\n";
    print CC "\n";

    print CC "const char *$msgdescclass\:\:getFieldStructName(int field)\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    if (field < $msgbasedescclass\:\:getFieldCount())\n";
        print CC "        return $msgbasedescclass\:\:getFieldStructName(field);\n";
        print CC "    field -= $msgbasedescclass\:\:getFieldCount();\n";
    }
    print CC "    switch (field) {\n";
    for ($i=0; $i<$fieldcount; $i++)
    {
        if ($fkind{$fieldlist[$i]} eq 'struct') {
            print CC "        case $i: return \"$ftype{$fieldlist[$i]}\"; break;\n";
        }
    }
    print CC "        default: return NULL;\n";
    print CC "    }\n";
    print CC "}\n";
    print CC "\n";

    print CC "void *$msgdescclass\:\:getFieldStructPointer(int field, int i)\n";
    print CC "{\n";
    if ($hasbasedescriptor) {
        print CC "    if (field < $msgbasedescclass\:\:getFieldCount())\n";
        print CC "        return $msgbasedescclass\:\:getFieldStructPointer(field, int i);\n";
        print CC "    field -= $msgbasedescclass\:\:getFieldCount();\n";
    }
    print CC "    switch (field) {\n";
    for ($i=0; $i<$fieldcount; $i++)
    {
        if ($fkind{$fieldlist[$i]} eq 'struct') {
            if ($fisarray{$fieldlist[$i]}) {
                print CC "        case $i: return (void *)&$getter{$fieldlist[$i]}(i); break;\n";
            } else {
                print CC "        case $i: return (void *)&$getter{$fieldlist[$i]}(); break;\n";
            }
        }
    }
    print CC "        default: return NULL;\n";
    print CC "    }\n";
    print CC "}\n";
    print CC "\n";

}

$crap = $msg;
if ($crap =~ /[^\s]/s)
{
    $crap =~ s/\n\n+/\n\n/sg;
    $crap =~ s/^\n//s;
    $crap =~ s/\n$//s;
    print STDERR "*** following parts of input file were not understood:\n";
    print STDERR "'$crap'\n";
}

close(H);
close(CC);

