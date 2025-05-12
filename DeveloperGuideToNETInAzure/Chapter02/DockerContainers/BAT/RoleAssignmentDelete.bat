REM !!!!! VALUE [6f0c96bc-335f-4cb6-89bb-768fc46f90ff] je PRINCIPAL ID MANAGED IDENTITY.
REM !!!!! VALUE [/subscriptions/b5f70a84-6ba2-4485-84cd-ac0883d618c5/resourceGroups/MyResources/providers/Microsoft.ContainerRegistry/registries/containertimmyanderson] je ID CONTAINER REGISTRY.

az role assignment delete --assignee "6f0c96bc-335f-4cb6-89bb-768fc46f90ff" --scope "/subscriptions/b5f70a84-6ba2-4485-84cd-ac0883d618c5/resourceGroups/MyResources/providers/Microsoft.ContainerRegistry/registries/containertimmyanderson" --role "AcrPull"