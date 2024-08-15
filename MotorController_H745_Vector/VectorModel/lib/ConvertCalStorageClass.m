ModelName = 'TRQCTL';

DictionaryObj = Simulink.data.dictionary.open([ModelName '.sldd']);
DataSectObj = getSection(DictionaryObj,'Design Data');
AllEntries = find(DataSectObj,'DataSource',[ModelName '.sldd']);

for i = 1:length(AllEntries)
    Entry = AllEntries(i);
    Value = getValue(Entry);
    if strcmp(class(Value),'Simulink.Parameter')
        ValueObjNew = CustomStorageClasses.Parameter();
        ValueObjNew.CoderInfo.StorageClass = 'Custom';
        ValueObjNew.CoderInfo.CustomStorageClass = 'Calibration';
        ValueObjNew.Value = Value.Value;
        ValueObjNew.DataType = Value.DataType;
        ValueObjNew.Unit = Value.Unit;
        setValue(Entry,ValueObjNew);
    end
end

saveChanges(DictionaryObj);
Simulink.data.dictionary.closeAll('-discard');